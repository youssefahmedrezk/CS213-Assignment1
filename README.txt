==============================================================
 CS213 Assignment 1 - Part 2 - Image Editor (Qt GUI)
==============================================================
Course     : CS213 Object Oriented Programming, FCAI, Cairo University
SuperVisor : Dr. Mohammad El-Ramly
Section    : S1

TEAM
  - Kholoud Mohamed Abd El-Rahman - 20250217
  - Demiana Samir Fawzy           - 20250219
  - Youssef Ahmed Rezk Ragab      - 20250755
  - Farha Mohamed Abd El-kareem   - 20251286


--------------------------------------------------------------
 1. TOOLS AND VERSIONS USED
--------------------------------------------------------------
  - Qt            : 6.12.0 (kit: Desktop Qt 6.12.0 MinGW 64-bit)
  - Qt Creator    : 20.0.2
  - Compiler      : MinGW 13.1.0 64-bit (the compiler that comes with Qt)
  - Build system  : qmake
  - Language      : C++17
  - Library       : Image_Class.h with stb_image.h and stb_image_write.h
                    (given by the course)
  - Note          : The filter functions were written by the team in
                    different editors. The submitted project is built and
                    tested with Qt Creator.


--------------------------------------------------------------
 2. FILES IN THIS PROJECT
--------------------------------------------------------------
  GUI.pro           :  The Qt project file (open this one)
  main.cpp          :  Starts the program (has the team header)
  mainwindow.h/.cpp :  The window, menu, buttons, load, save and undo
  filters.h         :  All the filter functions
  Image_Class.h     :  Image library given by the course
  stb_image.h       :  Image library given by the course
  stb_image_write.h :  Image library given by the course
  README.txt        :  This file
  links.txt         :  Link to the video and to the shared document


--------------------------------------------------------------
 3. HOW TO SET UP AND RUN
--------------------------------------------------------------
  1. Install Qt 6.12.0 with the "MinGW 64-bit" component and Qt Creator.
  2. Unzip the project to a folder with a short path.
  3. Open Qt Creator, choose File > Open File or Project, and select GUI.pro.
  4. Choose the kit "Desktop Qt 6.12.0 MinGW 64-bit" and click
     Configure Project.
  5. Click Build > Run qmake, then press the Build (hammer) button.
  6. Press the green Run button. The Image Editor window opens.


--------------------------------------------------------------
 4. HOW TO USE THE PROGRAM
--------------------------------------------------------------
  LOAD  : Load Image button or File > Load Image.
          Supported files: .jpg, .jpeg, .png, .bmp, .tga

  FILTERS : Click a numbered button (1 to 18) or use the Filters menu.
          Some filters open a small window that asks for a choice or a
          number. Press Cancel in that window to change nothing.

  UNDO :  Undo button, Edit > Undo, or Ctrl+Z.
          Goes back up to 20 steps.

  SAVE :  Save button or File > Save. It asks:
            - "Same file": replaces the original file.
            - "New file": saves a copy with a new name, then goes back to
              the original picture.
            - When you load a new image or exit, it asks if you want to save first.


--------------------------------------------------------------
 5. THE 18 FILTERS
--------------------------------------------------------------
  (Each filter shows: what it does, and what the program asks you.)

   1. Grayscale
        Turns the picture into shades of gray.
        Asks: nothing.

   2. Black and White
        Every pixel becomes pure black or pure white.
        Asks: nothing.

   3. Invert Image
        Reverses all colors, like a photo negative.
        Asks: nothing.

   4. Frame
        Adds a colored frame around the picture.
        Asks: Simple frame or Fancy frame, then the frame color.

   5. Flip Image
        Mirrors the picture.
        Asks: Horizontal or Vertical.

   6. Rotate Image
        Rotates the picture clockwise.
        Asks: 90, 180 or 270 degrees.

   7. Lighten / Darken
        Makes the picture 50% lighter or 50% darker.
        Asks: Lighten or Darken.

   8. Resize Image
        Changes the size of the picture.
        Asks: new width and new height (in pixels).

   9. Merge Images
        Blends the current picture with a second picture.
        Asks: the second image file, then how to merge:
          - Resize the smaller image, then merge, or
          - Merge the common area only.

  10. Detect Edges
        Shows the outlines of objects as black lines on white.
        Asks: nothing.

  11. Crop Image
        Cuts out a part of the picture.
        Asks: start x, start y, width and height.

  12. Blur
        Makes the picture soft and less detailed.
        Asks: blur level from 1 (light) to 3 (strong).

  13. Wano Sunlight
        Adds warm, bright sunlight to the picture.
        Asks: nothing.

  14. Old TV Effect
        Adds dark scan lines and white noise dots, like an old TV.
        Asks: nothing.

  15. Purple Filter
        Gives the picture a purple tint.
        Asks: nothing.

  16. Infrared
        Gives the picture a red infrared-photo look.
        Asks: nothing.

  17. Skew Image
        Slants the picture along the vertical axis.
        Asks: angle from -85 to 85 degrees.

  18. Oil Painting
        Makes the picture look like an oil painting.
        Asks: radius (1 to 10) and levels (2 to 20).
