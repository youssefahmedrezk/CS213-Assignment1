#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <vector>
#include <functional>

class QLabel;
class Image;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private slots:
    void loadClicked();
    void saveClicked();
    void undoClicked();

private:
    void showImage();
    bool saveTo(const QString &path);
    bool doSave();
    void runFilter(const std::function<bool()> &action);

    QLabel *imageLabel;
    Image *image;
    std::vector<Image> *history;
    QString currentName;
    bool loaded = false;
};

#endif