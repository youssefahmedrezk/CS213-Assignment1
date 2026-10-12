#include "mainwindow.h"
#include "filters.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QInputDialog>
#include <QColor>
#include <QColorDialog>
#include <QCloseEvent>
#include <QImage>
#include <QPixmap>
#include <QStringList>

// ---------- helper functions (GUI versions of the filters that used cin) ----------

static int askChoice(QWidget *parent, const QString &title,
                     const QString &label, const QStringList &items)
{
    bool ok = false;
    QString s = QInputDialog::getItem(parent, title, label, items, 0, false, &ok);
    if (!ok)
        return -1;
    return items.indexOf(s);
}

static void frame_gui(Image &image, int choice, const QColor &color)
{
    int cr = color.red();
    int cg = color.green();
    int cb = color.blue();

    if (choice == 0) {
        // simple frame: one band of the chosen color
        int frameshape = 10;
        for (int i = 0; i < image.height; i++) {
            for (int j = 0; j < image.width; j++) {
                if (i < frameshape || i >= image.height - frameshape ||
                    j < frameshape || j >= image.width - frameshape) {
                    image(j, i, 0) = cr;
                    image(j, i, 1) = cg;
                    image(j, i, 2) = cb;
                }
            }
        }
    } else {
        // fancy frame: chosen color, white line, chosen color
        int t = 3;
        for (int i = 0; i < image.height; i++) {
            for (int j = 0; j < image.width; j++) {
                if (i < t || i >= image.height - t || j < t || j >= image.width - t) {
                    image(j, i, 0) = cr; image(j, i, 1) = cg; image(j, i, 2) = cb;
                } else if (i < t * 2 || i >= image.height - t * 2 ||
                           j < t * 2 || j >= image.width - t * 2) {
                    image(j, i, 0) = 255; image(j, i, 1) = 255; image(j, i, 2) = 255;
                } else if (i < t * 3 || i >= image.height - t * 3 ||
                           j < t * 3 || j >= image.width - t * 3) {
                    image(j, i, 0) = cr; image(j, i, 1) = cg; image(j, i, 2) = cb;
                }
            }
        }
    }
}

static void resize_gui(Image &image, int newwidth, int newheight)
{
    double widthratio = image.width / (double)newwidth;
    double heightratio = image.height / (double)newheight;

    Image copy(newwidth, newheight);
    for (int i = 0; i < newheight; i++) {
        for (int j = 0; j < newwidth; j++) {
            int y = i * heightratio;
            int x = j * widthratio;
            for (int c = 0; c < 3; c++)
                copy(j, i, c) = image(x, y, c);
        }
    }
    image = copy;
}

static void crop_gui(Image &image, int x, int y, int w, int h)
{
    Image cropped(w, h);
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
            for (int k = 0; k < 3; k++)
                cropped(i, j, k) = image(x + i, y + j, k);
    image = cropped;
}

static void blur_gui(Image &image, int level)
{
    Image oldimage = image;

    int r = 3;
    if (level == 2) r = 7;
    else if (level == 3) r = 9;

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int sumr = 0, sumg = 0, sumb = 0, count = 0;
            for (int di = -r; di <= r; di++) {
                for (int dj = -r; dj <= r; dj++) {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < image.width && nj >= 0 && nj < image.height) {
                        sumr += oldimage(ni, nj, 0);
                        sumg += oldimage(ni, nj, 1);
                        sumb += oldimage(ni, nj, 2);
                        count++;
                    }
                }
            }
            image(i, j, 0) = sumr / count;
            image(i, j, 1) = sumg / count;
            image(i, j, 2) = sumb / count;
        }
    }
}

// ---------- the window ----------

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    image = new Image();
    history = new std::vector<Image>();

    resize(900, 760);
    setWindowTitle("Image Editor");

    imageLabel = new QLabel("No image loaded");
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setMinimumSize(400, 300);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setStyleSheet("background-color: #2b2b2b; color: white;");

    // ----- menu bar -----
    QMenu *fileMenu = menuBar()->addMenu("&File");
    QMenu *editMenu = menuBar()->addMenu("&Edit");
    QMenu *filtersMenu = menuBar()->addMenu("Fi&lters");

    QAction *openAct = fileMenu->addAction("Load Image");
    openAct->setShortcut(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &MainWindow::loadClicked);

    QAction *saveAct = fileMenu->addAction("Save");
    saveAct->setShortcut(QKeySequence::Save);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveClicked);

    QAction *exitAct = fileMenu->addAction("Exit");
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    QAction *undoAct = editMenu->addAction("Undo");
    undoAct->setShortcut(QKeySequence::Undo);
    connect(undoAct, &QAction::triggered, this, &MainWindow::undoClicked);

    // ----- numbered filter buttons + menu items -----
    QGridLayout *grid = new QGridLayout;
    int num = 1;
    auto addFilter = [&](const QString &name, std::function<bool()> action) {
        QString text = QString("%1: %2").arg(num).arg(name);

        QAction *act = filtersMenu->addAction(text);
        connect(act, &QAction::triggered, this, [this, action]() { runFilter(action); });

        QPushButton *b = new QPushButton(text);
        connect(b, &QPushButton::clicked, this, [this, action]() { runFilter(action); });
        grid->addWidget(b, (num - 1) / 3, (num - 1) % 3);

        num++;
    };

    // 1
    addFilter("Grayscale", [this]() { gray_scale(*image); return true; });

    // 2
    addFilter("Black and White", [this]() { black_and_white(*image); return true; });

    // 3
    addFilter("Invert Image", [this]() { invert_color(*image); return true; });

    // 4
    addFilter("Frame", [this]() {
        int c = askChoice(this, "Frame", "Choose the frame:",
                          {"Simple frame", "Fancy frame"});
        if (c < 0) return false;
        QColor color = QColorDialog::getColor(Qt::green, this, "Choose the frame color");
        if (!color.isValid()) return false;
        frame_gui(*image, c, color);
        return true;
    });

    // 5
    addFilter("Flip Image", [this]() {
        int c = askChoice(this, "Flip", "Choose the direction:",
                          {"Horizontal", "Vertical"});
        if (c < 0) return false;
        if (c == 0) horizontal_image(*image);
        else vertical_image(*image);
        return true;
    });

    // 6
    addFilter("Rotate Image", [this]() {
        QStringList items = {"90", "180", "270"};
        int c = askChoice(this, "Rotate", "Choose the degree:", items);
        if (c < 0) return false;
        *image = rotate_image(*image, items[c].toInt());
        return true;
    });

    // 7
    addFilter("Lighten / Darken", [this]() {
        int c = askChoice(this, "Lighten / Darken", "Choose the mode:",
                          {"Lighten", "Darken"});
        if (c < 0) return false;
        lighten_darken(*image, c + 1);
        return true;
    });

    // 8
    addFilter("Resize Image", [this]() {
        bool ok = false;
        int w = QInputDialog::getInt(this, "Resize",
                                     QString("Current size: %1 x %2\nNew width:").arg(image->width).arg(image->height),
                                     image->width, 1, 10000, 1, &ok);
        if (!ok) return false;
        int h = QInputDialog::getInt(this, "Resize", "New height:",
                                     image->height, 1, 10000, 1, &ok);
        if (!ok) return false;
        resize_gui(*image, w, h);
        return true;
    });

    // 9
    addFilter("Merge Images", [this]() {
        QString f = QFileDialog::getOpenFileName(
            this, "Choose the second image", "",
            "Images (*.png *.jpg *.jpeg *.bmp *.tga)");
        if (f.isEmpty()) return false;

        Image image2;
        try {
            image2.loadNewImage(f.toStdString());
        } catch (std::exception &e) {
            QMessageBox::warning(this, "Error", e.what());
            return false;
        }

        int c = askChoice(this, "Merge", "How to merge?",
                          {"Resize the smaller image, then merge",
                           "Merge the common area only"});
        if (c < 0) return false;
        if (c == 0) resizing_images(*image, image2);
        else common_area_merge(*image, image2);
        return true;
    });

    // 10
    addFilter("Detect Edges", [this]() {
        Image edges(image->width, image->height);
        detectEdges(*image, edges, 20);
        *image = edges;
        return true;
    });

    // 11
    addFilter("Crop Image", [this]() {
        bool ok = false;
        QString info = QString("Image size: %1 x %2\n").arg(image->width).arg(image->height);
        int x = QInputDialog::getInt(this, "Crop", info + "Start x:",
                                     0, 0, image->width - 1, 1, &ok);
        if (!ok) return false;
        int y = QInputDialog::getInt(this, "Crop", info + "Start y:",
                                     0, 0, image->height - 1, 1, &ok);
        if (!ok) return false;
        int w = QInputDialog::getInt(this, "Crop", info + "Width:",
                                     image->width - x, 1, image->width - x, 1, &ok);
        if (!ok) return false;
        int h = QInputDialog::getInt(this, "Crop", info + "Height:",
                                     image->height - y, 1, image->height - y, 1, &ok);
        if (!ok) return false;
        crop_gui(*image, x, y, w, h);
        return true;
    });

    // 12
    addFilter("Blur", [this]() {
        bool ok = false;
        int level = QInputDialog::getInt(this, "Blur", "Level (1 to 3):",
                                         1, 1, 3, 1, &ok);
        if (!ok) return false;
        blur_gui(*image, level);
        return true;
    });

    // 13
    addFilter("Wano Sunlight", [this]() { sun_light(*image); return true; });

    // 14
    addFilter("Old TV Effect", [this]() { img_effect(*image); return true; });

    // 15
    addFilter("Purple Filter", [this]() { purple_image(*image); return true; });

    // 16
    addFilter("Infrared", [this]() { infraredfilter(*image); return true; });

    // 17
    addFilter("Skew Image", [this]() {
        bool ok = false;
        double angle = QInputDialog::getDouble(this, "Skew",
                                               "Angle (-85 to 85):", 30, -85, 85, 1, &ok);
        if (!ok) return false;
        *image = skewing(*image, angle);
        return true;
    });

    // 18
    addFilter("Oil Painting", [this]() {
        bool ok = false;
        int radius = QInputDialog::getInt(this, "Oil Painting", "Radius (1 to 10):",
                                          3, 1, 10, 1, &ok);
        if (!ok) return false;
        int levels = QInputDialog::getInt(this, "Oil Painting", "Levels (2 to 20):",
                                          10, 2, 20, 1, &ok);
        if (!ok) return false;
        Image output(image->width, image->height);
        oil(*image, output, radius, levels);
        *image = output;
        return true;
    });

    // ----- bottom buttons -----
    QPushButton *loadBtn = new QPushButton("Load Image");
    QPushButton *saveBtn = new QPushButton("Save");
    QPushButton *undoBtn = new QPushButton("Undo");
    connect(loadBtn, &QPushButton::clicked, this, &MainWindow::loadClicked);
    connect(saveBtn, &QPushButton::clicked, this, &MainWindow::saveClicked);
    connect(undoBtn, &QPushButton::clicked, this, &MainWindow::undoClicked);

    QHBoxLayout *bottom = new QHBoxLayout;
    bottom->addWidget(loadBtn);
    bottom->addWidget(saveBtn);
    bottom->addWidget(undoBtn);

    QWidget *central = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->addWidget(imageLabel, 1);
    layout->addLayout(grid);
    layout->addLayout(bottom);
    setCentralWidget(central);
}

MainWindow::~MainWindow()
{
    delete history;
    delete image;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if (loaded)
        showImage();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (loaded) {
        auto answer = QMessageBox::question(
            this, "Exit", "Save the current image before exit?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (answer == QMessageBox::Cancel) {
            event->ignore();
            return;
        }
        if (answer == QMessageBox::Yes && !doSave()) {
            event->ignore();    // the user cancelled the save
            return;
        }
    }
    event->accept();
}

void MainWindow::runFilter(const std::function<bool()> &action)
{
    if (!loaded) {
        QMessageBox::information(this, "No image", "Load an image first.");
        return;
    }

    Image backup = *image;      // keep a copy for Undo
    if (!action())              // user pressed Cancel
        return;

    history->push_back(backup);
    if (history->size() > 20)
        history->erase(history->begin());

    showImage();
}

void MainWindow::undoClicked()
{
    if (history->empty()) {
        QMessageBox::information(this, "Undo", "Nothing to undo.");
        return;
    }
    *image = history->back();
    history->pop_back();
    showImage();
}

void MainWindow::loadClicked()
{
    // ask to save the current image first
    if (loaded) {
        auto answer = QMessageBox::question(
            this, "Load a new image",
            "Save the current image before loading a new one?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (answer == QMessageBox::Cancel)
            return;
        if (answer == QMessageBox::Yes && !doSave())
            return;             // the user cancelled the save
    }

    QString file = QFileDialog::getOpenFileName(
        this, "Open image", "", "Images (*.png *.jpg *.jpeg *.bmp *.tga)");
    if (file.isEmpty())
        return;

    try {
        image->loadNewImage(file.toStdString());
        currentName = file;
        loaded = true;
        history->clear();
        showImage();
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

bool MainWindow::saveTo(const QString &path)
{
    try {
        image->saveImage(path.toStdString());
        QMessageBox::information(this, "Saved", "Image saved.");
        return true;
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Error", e.what());
        return false;
    }
}

// returns true if the image was saved, false if the user cancelled or it failed
bool MainWindow::doSave()
{
    if (!loaded) {
        QMessageBox::information(this, "No image", "Load an image first.");
        return false;
    }

    QMessageBox box(this);
    box.setWindowTitle("Save");
    box.setText("How do you want to save?");
    QPushButton *sameBtn = box.addButton("Same file (replace the original)",
                                         QMessageBox::ActionRole);
    QPushButton *newBtn = box.addButton("New file (then go back to the original)",
                                        QMessageBox::ActionRole);
    box.addButton("Cancel", QMessageBox::RejectRole);
    box.exec();

    if (box.clickedButton() == sameBtn) {
        return saveTo(currentName);
    }

    if (box.clickedButton() == newBtn) {
        QString file = QFileDialog::getSaveFileName(
            this, "Save image as", "", "Images (*.png *.jpg *.jpeg *.bmp *.tga)");
        if (file.isEmpty())
            return false;

        // check the extension
        QString ext = QFileInfo(file).suffix().toLower();
        if (ext.isEmpty()) {
            file += ".png";
        } else if (ext != "jpg" && ext != "jpeg" && ext != "png" &&
                   ext != "bmp" && ext != "tga") {
            QMessageBox::warning(this, "Invalid extension",
                                 "Please use .jpg, .jpeg, .png, .bmp or .tga");
            return false;
        }

        if (!saveTo(file))
            return false;

        // go back to the original picture
        try {
            image->loadNewImage(currentName.toStdString());
            history->clear();
            showImage();
        } catch (std::exception &e) {
            QMessageBox::warning(this, "Error", e.what());
        }
        return true;
    }

    return false;               // Cancel
}

void MainWindow::saveClicked()
{
    doSave();
}

void MainWindow::showImage()
{
    QImage q(image->width, image->height, QImage::Format_RGB32);
    for (int x = 0; x < image->width; x++)
        for (int y = 0; y < image->height; y++)
            q.setPixel(x, y, qRgb((*image)(x, y, 0),
                                  (*image)(x, y, 1),
                                  (*image)(x, y, 2)));

    QPixmap pm = QPixmap::fromImage(q);

    // shrink only if the picture is bigger than the area, never enlarge
    if (pm.width() > imageLabel->width() || pm.height() > imageLabel->height())
        pm = pm.scaled(imageLabel->size(), Qt::KeepAspectRatio,
                       Qt::SmoothTransformation);

    imageLabel->setPixmap(pm);
    setWindowTitle(QString("Image Editor - %1 x %2")
                       .arg(image->width).arg(image->height));
}