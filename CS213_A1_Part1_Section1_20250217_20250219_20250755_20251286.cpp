/*
 * File: CS213_A1_Part1_Section1_20250217_20250219_20250755_20251286.cpp
 * Purpose: Image processing program (console app). It loads an image,
 *          applies filters, and saves the result. Part 1 of Assignment 1.
 *
 * Course: CS213 Object Oriented Programming, FCAI, Cairo University
 * Instructor: Dr. Mohammad El-Ramly
 * Section: (S1) 
 * TA: Mennat Allah Mamdouh
 * Team:
 *   1. Kholoud Mahmoud Abd El-Rahman - ID: 20250217
 *   2. Farha Mahamoud Abd El-kareem - ID: 20251286
 *   3. Youssef Ahmed Rezk Ragab - ID: 20250755
 *   4. Demiana Samir Fawzy - ID: 20250219
 *
 * Who did what:
 *   Kholoud: Filter 1 (Grayscale), Filter 5 (Flip)
 *   Demiana: Filter 2 (white and black), Filter 6 (Rotate)
 *   Youssef: Filter 3 (Invert), Filter 7 (Lighten and Darken)
 *   Farha:   Filter 4 (Frame), Filter 8 (Resize)
 *   Menu and main function were implemented by all team members.
 */
#include "Image_Class.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;


void invert_color(Image& image) {
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height ; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                image(i,j,k) = 255 -image(i,j,k);
         
            }
            
        }
        
    }
}

void lighten_darken(Image& image,int mode) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {
                if (mode == 1)
                {
                    image(i,j,k) = image(i,j,k)+(255-image(i,j,k))/2;
                }
                else if (mode ==2)
                {
                    image(i,j,k) = image(i,j,k)/2;
                }
            }
        }
    }
}

void gray_scale(Image& image) {
    for (int i =0;i< image.width ;i++) {
        for (int j =0;j<image.height;j++) {
            for (int k=0;k<image.channels;k++) {
                int avr= (image(i,j,0)+image(i,j,1)+image(i,j,2))/3;
                image(i,j,0)=avr;
                image(i,j,1)=avr;
                image(i,j,2)=avr;


            }
        }
    }
}

void horizontal_image(Image& image) {
    for (int i =0;i< (image.width/2) ;i++) {
        for (int j =0;j<(image.height);j++) {
            for (int k =0;k<3;k++) {
                swap(image(image.width-1-i,j,k),image(i,j,k));
            }

        }
    }
}
void vertical_image(Image& image) {
    for (int i =0;i< (image.width) ;i++) {
        for (int j =0;j<(image.height/2);j++) {
            for (int k =0;k<3;k++) {
                swap(image(i,image.height-1-j,k),image(i,j,k));
            }

        }
    }
}

void frame(Image& image){
   int choice;
    cout << "choose the frame"<<endl;
    cout<<"1. simple frame"<<endl;
    cout<<"2. fancy frame"<<endl;
    cout<<"please choose the frame: ";
    cin>>choice;
    int frameshape= 10;
    
    if(choice==1){
        for(int i=0; i<image.height; i++){
        for(int j=0; j<image.width; j++){
            if(i<frameshape||i>=image.height-frameshape||j<frameshape||
                j>=image.width-frameshape){
                    image(j,i,0)=0;
                    image(j,i,1)=255;
                    image(j,i,2)=0;
            }
        }
    }
    }
    else if(choice==2){
    int linethick=frameshape /3;
    if(linethick<1)linethick=1;
    for(int i=0; i<image.height; i++){
        for(int j=0; j<image.width; j++){
            if(i<linethick|| i>=image.height-linethick||
            j<linethick|| j>=image.width-linethick){
                image(j,i,0)=255;
                image(j,i,1)=0;
                image(j,i,2)=0;
            }
            else if(i<linethick*2 || i>=image.height-linethick*2||
            j<linethick*2 || j>=image.width-linethick*2){
                image(j,i,0)=0;
                image(j,i,1)=255;
                image(j,i,2)=0;
            }
            else if (i<linethick*3 || i>=image.height-linethick*3||
                j<linethick*3 || j>=image.width-linethick*3){
                image(j,i,0)=0;
                image(j,i,1)=0;
                image(j,i,2)=255;

            }
    
        }
    }
    }
}

void applyresize(Image& image){
    int newwidth ,newheight;
    cout<<"enter the new width and height respectively: ";
    cin>>newwidth>>newheight;
    double widthratio = image.width / (double)newwidth;
    double heightratio = image.height / (double)newheight;
    Image copy(newwidth, newheight) ;  
    for(int i=0; i<newheight; i++){
       for(int j=0; j<newwidth; j++){
           int y = i * heightratio;
           int x = j * widthratio;
           for(int c =0 ; c < 3; c++){
             copy(j,i,c)= image(x,y,c);

           }
        }
    }
    image = copy;
}
void black_and_white(Image& image) {
    for (int i =0;i< image.width ;i++) {
        for (int j =0;j<image.height;j++) {
            for (int k=1;k<image.channels;k++) {

                int avr= (image(i,j,0)+image(i,j,1)+image(i,j,2))/3;
                image(i,j,0)=avr;
                image(i,j,1)=avr;
                image(i,j,2)=avr;

                if (avr >= 127.5)
                    avr =255;
                else
                    avr = 0;
                image(i,j,0) = avr;
                image(i,j,1) = avr;
                image(i,j,2) = avr;


            }
        }

    }



}
Image rotate_image(const Image& image, int degree) {

    switch (degree) {

        case 90: {
            Image output(image.height, image.width);

            for (int x = 0; x < image.width; x++)
                for (int y = 0; y < image.height; y++)
                    for (int c = 0; c < image.channels; c++)
                        output(image.height - 1 - y, x, c) = image(x, y, c);

            return output;
        }

        case 180: {
            Image output(image.width, image.height);

            for (int x = 0; x < image.width; x++)
                for (int y = 0; y < image.height; y++)
                    for (int c = 0; c < image.channels; c++)
                        output(image.width - 1 - x, image.height - 1 - y, c) = image(x, y, c);

            return output;
        }

        case 270: {
            Image output(image.height, image.width);

            for (int x = 0; x < image.width; x++)
                for (int y = 0; y < image.height; y++)
                    for (int c = 0; c < image.channels; c++)
                        output(y, image.width - 1 - x, c) = image(x, y, c);

            return output;
        }

        default:
            return image;
    }
}

void crop_image(Image& image){
    int x, y, w, h;
    while (true){
        cout << "Image size: " << image.width << " x " << image.height << endl;    
        cout << "Enter start point x y: ";
        cin >> x >> y;
        cout << "Enter width height: ";
        cin >> w >> h;
        
        if (x >= 0 && y >= 0 && w > 0 && h > 0 && x + w <= image.width && y + h <= image.height) {
            break;
        }
        else{
            cout<<"Wrong dimensions, try again." << endl;
        }
    }
    Image cropped(w, h);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
             for (int k = 0; k < 3; k++) {
                 cropped(i, j, k) = image(x + i, y + j, k);
             }
        }
    }
    image = cropped;
}

void purple_image(Image& image){
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            image(i, j, 0) = image(i, j, 0)*0.90;
            image(i, j, 1) = image(i, j, 1)*0.70; 
        }
    }
}

void sun_light (Image & image) {
    for (int i = 0 ; i < image.width ; i++) {
        for (int j = 0 ; j < image.height ; j++) {
            image(i,j,0) = image(i,j,0)+(255-image(i,j,0))/2;
            image(i,j,1) = image(i,j,1)+(255-image(i,j,1))/2;


        }
    }
}

void merge_images(Image &image1, Image &image2, int new_width, int new_height){
    Image merged_image(new_width, new_height);

    for (int i = 0; i < new_width; i++)
    {
        for (int j = 0; j < new_height; j++)
        {
            merged_image(i, j, 0) =(image1(i, j, 0) + image2(i, j, 0)) / 2;

            merged_image(i, j, 1) =(image1(i, j, 1) + image2(i, j, 1)) / 2;

            merged_image(i, j, 2) =(image1(i, j, 2) + image2(i, j, 2)) / 2;
        }
    }

    merged_image.saveImage("merged.jpg");
}

void resizing_images(Image &image1, Image &image2)
{
    if (image1.height > image2.height or image1.width > image2.width) //image 2 small
    {
        Image resized_image2(image1.width, image1.height);

        double ratio_w2 = double(image2.width) / image1.width;

        double ratio_h2 = double(image2.height) / image1.height;

        for (int i = 0; i < image1.width; i++)
        {
            for (int j = 0; j < image1.height; j++)
            {
                int old_width = i * ratio_w2;
                int old_height = j * ratio_h2;

                for (int k = 0; k < 3; k++)
                {
                    resized_image2(i, j, k) = image2(old_width, old_height, k);
                }
            }
        }

        merge_images(image1,resized_image2,image1.width,image1.height);
    }

    else if (image2.height > image1.height or image2.width > image1.width) //image 1 small
    {
        Image resized_image1(image2.width, image2.height);

        double ratio_w1 =double(image1.width) / image2.width;

        double ratio_h1 =double(image1.height) / image2.height;

        for (int i = 0; i < image2.width; i++)
        {
            for (int j = 0; j < image2.height; j++)
            {
                int old_width = i * ratio_w1;
                int old_height = j * ratio_h1;

                for (int k = 0; k < 3; k++)
                {
                    resized_image1(i, j, k) = image1(old_width, old_height, k);
                }
            }
        }

        merge_images(resized_image1,image2,image2.width,image2.height);
    }
    else if (image1.width == image2.height && image2.width == image1.width) {
         merge_images(image1,image2,image1.width,image1.height);
    }

}

void common_area_merge(Image &image1, Image &image2)
{
    int common_width = min(image1.width, image2.width);

    int common_height =min(image1.height, image2.height);

    Image merged_image(common_width, common_height);

    for (int i = 0; i < common_width; i++)
    {
        for (int j = 0; j < common_height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                merged_image(i, j, k) =(image1(i, j, k)+ image2(i, j, k)) / 2;
            }
        }
    }

    merged_image.saveImage("common_area.jpg");
}


void loadImage(Image& image, string& currentName) {
    while (true) {
        cout << "Enter the name of the image file (with valid extension): ";
        string filename;
        cin >> filename;
        try {
            image.loadNewImage(filename);
            currentName = filename;
            break;
        } catch (exception& e) {
            cout << e.what() << endl;
            cout << "Please try again." << endl;
        }
    }
}
void saveCurrent(Image& image, string& currentName) {
    while (true) {
        cout << "Save on the same file or a new name? (1 = same, 2 = new): ";
        int option;
        cin >> option;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a number." << endl;
            continue;
        }

        string name;
        if (option == 1) {
            name = currentName;
        } else if (option == 2) {
            cout << "Enter the new file name (with extension): ";
            cin >> name;
        } else {
            cout << "Please enter 1 or 2." << endl;
            continue;
        }

        try {
            image.saveImage(name);
            currentName = name;
            cout << "Image saved." << endl;
            break;
        } catch (exception& e) {
            cout << e.what() << endl;
            cout << "Please try again." << endl;
        }
    }
}
int main() {
    Image image;
    cout << "Welcome to the Image Processing Program!" << endl;
    string currentName;
    loadImage(image, currentName);
    
while (true) {
    cout << "0: Load New Image" << endl;
    cout << "1: Grayscale Conversion" << endl;
    cout << "2: Black and White" << endl;
    cout << "3: Invert Image" << endl;
    cout << "4: Adding a Frame" << endl;
    cout << "5: Flip Image" << endl;
    cout << "6: Rotate Image" << endl;
    cout << "7: Darken and Lighten Image" << endl;
    cout << "8: Resizing Images" << endl;
    cout << "9: Save Image" << endl;
    cout << "10: Exit" << endl;
    cout << "Choose from 0 to 10: ";

    int filter_num;
    cin >> filter_num;
    if (cin.fail()) {
       cin.clear();
       cin.ignore(10000, '\n');
       cout << "Please enter a number." << endl;
       continue;
    }
    cin.ignore(10000, '\n');
    switch (filter_num) {
        case 0: {
           char answer;
           cout << "Save the current image first? (y/n): ";
           cin >> answer;
           answer = tolower(answer);
           if (answer == 'y') {
               saveCurrent(image, currentName);
           }
           loadImage(image, currentName);
           break;
        } 
        case 1:
            gray_scale(image);
            break;
        case 2:
            black_and_white(image);
            break;
        case 3:
            invert_color(image);
            break;
        case 4:
            frame(image);
            break;
        case 5: {
            while (true) {
              int mode;
              cout << "1: vertical"<<endl;
              cout<<"2:horizontal"<<endl;
              cout<<"please choose the mode: ";
              cin >> mode;
              if (cin.fail()) {
                 cin.clear();
                 cin.ignore(10000, '\n');
                 cout << "Please enter a number." << endl;
                 continue;
              }
              if (mode == 1){
                 vertical_image(image);
                 break;
              } 
              else if (mode == 2){
                  horizontal_image(image);
                  break;
              } 
              else{
                  cout<<"Invalid mode. Please choose 1 or 2."<<endl;
               } 
            }
            break; 
        } 
        case 6:{
            int degree;
            cout << "Enter the degree of rotation (90, 180, 270): ";
            cin >> degree;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Please enter a number." << endl;
                continue;
            }
            image = rotate_image(image, degree);
            break;
        }
            
        case 7: {
            while (true){
                int mode;
                cout << "1: lighten Image"<<endl;
                cout<<"2: Darken Image"<<endl;
                cout<<"please choose the mode: "<<endl;
                cin >> mode;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Please enter a number." << endl;
                    continue;
                } 
                if (mode == 1 || mode == 2) {
                    lighten_darken(image, mode);
                    break;
                }
                else {
                    cout << "Invalid mode. Please choose 1 or 2." << endl;
                }
            }
            break;
        }
        case 8:
            applyresize(image);
            break;
        case 9:
            saveCurrent(image, currentName);
            break;
        case 10:{
            char answer;
            cout << "Save before exit? (y/n): ";
            cin >> answer;
            answer = tolower(answer);
            if (answer == 'y') {
               saveCurrent(image, currentName);
            }
            return 0;
        }   
        default:
            cout << "invalid choice" << endl;
    }
}
    return 0;
}
