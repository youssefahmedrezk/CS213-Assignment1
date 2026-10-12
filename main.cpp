/*
 * File: main.cpp
 * Purpose: Image Editor with a Qt GUI. It loads an image, applies 18 filters,
 *          supports Undo, and saves the result (same file or a new file).
 *          Part 2 of Assignment 1.
 *
 * Course: CS213 Object Oriented Programming, FCAI, Cairo University
 * SuperVisor: Dr. Mohammad El-Ramly
 * Section: (S1)
 * TA: Mennat Allah Mamdouh
 * Team:
 *   1. Kholoud Mohamed Abd El-Rahman - ID: 20250217
 *   2. Demiana Samir Fawzy - ID: 20250219
 *   3. Youssef Ahmed Rezk Ragab - ID: 20250755
 *   4. Farha Mohamed Abd El-kareem - ID: 20251286
 *
 * Who did what:
 *   Kholoud: Filter 1 (Grayscale), Filter 5 (Flip), Filter 9 (Merge),
 *            Filter 13 (Wano Sunlight), the GUI
 *   Demiana: Filter 2 (Black and White), Filter 6 (Rotate),
 *            Filter 10 (Detect Edges), Filter 14 (Old TV), Filter 18 (Oil Painting)
 *   Youssef: Filter 3 (Invert), Filter 7 (Lighten and Darken),
 *            Filter 11 (Crop), Filter 15 (Purple), the GUI
 *            (window, menu, buttons, load, save, undo)
 *   Farha:   Filter 4 (Frame), Filter 8 (Resize), Filter 12 (Blur),
 *            Filter 16 (Infrared), Filter 17 (Skew)
 *
 * Menu (the program shows these options):
 *   File    -> Load Image, Save, Exit
 *   Edit    -> Undo
 *   Filters -> 1 to 18 (the same filters are also numbered buttons in the window)
 *
 * Files: main.cpp (starts the program), mainwindow.h / mainwindow.cpp (the GUI),
 *        filters.h (all the filter functions), Image_Class.h (given library).
 */
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}