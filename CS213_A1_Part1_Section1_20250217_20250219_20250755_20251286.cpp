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
 *   1. Kholoud Mohamed Abd El-Rahman - ID: 20250217
 *   2. Farha Mohamed Abd El-kareem - ID: 20251286
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
# include<vector>
#include <cstdlib>
#include <cmath>

using namespace std;
// Filter 1: Grayscale Conversion ---- kholoud
void gray_scale(Image& image) {
    for (int i =0;i< image.width ;i++) {
        for (int j =0;j<image.height;j++) {
                int avr= (image(i,j,0)+image(i,j,1)+image(i,j,2))/3;
                image(i,j,0)=avr;
                image(i,j,1)=avr;
                image(i,j,2)=avr;

        }
    }
}

//===================================================================================================================

// Filter 2: Black and White ---- demiana
void black_and_white(Image& image) {
    for (int i =0;i< image.width ;i++) {
        for (int j =0;j<image.height;j++) {
                int avr= (image(i,j,0)+image(i,j,1)+image(i,j,2))/3;
                image(i,j,0)=avr;
                image(i,j,1)=avr;
                image(i,j,2)=avr;

                if (avr >= 128)
                    avr =255;
                else
                    avr = 0;

                image(i,j,0) = avr;
                image(i,j,1) = avr;
                image(i,j,2) = avr;
            }
        }
    }


//======================================================================================================

// Filter 3: Invert Image --youssef
void invert_color(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height ; j++) {
            for (int k = 0; k < 3; k++) {
                image(i,j,k) = 255 -image(i,j,k);
            }
        }
    }
}

//====================================================================================

// Filter 4: Adding a Frame to the Picture --farha
void frame(Image& image){
   int choice;

    cout << "choose the frame"<<endl;
    cout<<"1. simple frame"<<endl;
    cout<<"2. fancy frame"<<endl;
    cout<<"please choose the frame: ";

    while (true) {
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a number." << endl;
            continue;
        }

        if (choice == 1 || choice == 2)
            break;

        cout << "Please choose 1 or 2: ";
    }
    int frameshape= 10;

    if(choice==1){
        for(int i=0; i<image.height; i++){
            for(int j=0; j<image.width; j++){
                if(i<frameshape||i>=image.height-frameshape||j<frameshape||j>=image.width-frameshape){
                    image(j,i,0)=0;
                    image(j,i,1)=255;
                    image(j,i,2)=0;
                }
            }
        }
    }

    else if(choice==2){

        int linethick=frameshape /3;

        if(linethick<1)
            linethick=1;

        for(int i=0; i<image.height; i++){
            for(int j=0; j<image.width; j++){
                if(i<linethick||i>=image.height-linethick||j<linethick||j>=image.width-linethick){
                    image(j,i,0)=255;
                    image(j,i,1)=0;
                    image(j,i,2)=0;
                }

                else if(i<linethick*2 ||i>=image.height-linethick*2||j<linethick*2 ||j>=image.width-linethick*2){
                    image(j,i,0)=0;
                    image(j,i,1)=255;
                    image(j,i,2)=0;
                }

                else if (i<linethick*3 ||i>=image.height-linethick*3||j<linethick*3 ||j>=image.width-linethick*3){
                    image(j,i,0)=0;
                    image(j,i,1)=0;
                    image(j,i,2)=255;
                }
            }
        }
    }

}

//================================================================================

// Filter 5: Flip Image (Horizontal)   ---- kholoud
void horizontal_image(Image& image) {
    for (int i =0;i< (image.width/2) ;i++) {
        for (int j =0;j<(image.height);j++) {
            for (int k =0;k<3;k++) {
                swap(image(image.width-1-i,j,k),image(i,j,k));
            }
        }
    }
}

//============================================================================================================

// Filter 5: Flip Image (Vertical)  ---- kholoud
void vertical_image(Image& image) {
    for (int i =0;i< (image.width) ;i++) {
        for (int j =0;j<(image.height/2);j++) {
            for (int k =0;k<3;k++) {
                swap(image(i,image.height-1-j,k),image(i,j,k));
            }
        }
    }
}

//================================================================================================

// Filter 6: Rotate Image --demiana
Image rotate_image(const Image& image, int degree) {

    switch (degree) {

        case 90: {
            Image output(image.height, image.width);

            for (int x = 0; x < image.width; x++)
                for (int y = 0; y < image.height; y++)
                    for (int c = 0; c < 3; c++)
                        output(image.height - 1 - y, x, c) = image(x, y, c);

            return output;
        }

        case 180: {
            Image output(image.width, image.height);

            for (int x = 0; x < image.width; x++)
                for (int y = 0; y < image.height; y++)
                    for (int c = 0; c < 3; c++)
                        output(image.width - 1 - x,
                               image.height - 1 - y,
                               c) = image(x, y, c);

            return output;
        }

        case 270: {
            Image output(image.height, image.width);

            for (int x = 0; x < image.width; x++)
                for (int y = 0; y < image.height; y++)
                    for (int c = 0; c < 3; c++)
                        output(y,
                               image.width - 1 - x,
                               c) = image(x, y, c);

            return output;
        }

        default:
            cout << "Invalid degree" << endl;
            return image;
    }
}
//=========================================================================================================================
// Filter 7: Darken and Lighten Image --youssef
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

//==================================================================================================

// Filter 8: Resizing Images --farha
void applyresize(Image& image){
    int newwidth ,newheight;
    cout << "Enter the new width and height respectively: ";
    cin >> newwidth >> newheight;
    while (cin.fail() || newwidth <= 0 || newheight <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Invalid dimensions. Enter again: ";
        cin >> newwidth >> newheight;
    }

    double widthratio = image.width / (double)newwidth;
    double heightratio = image.height / (double)newheight;

    Image copy(newwidth, newheight);

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

//===================================================================================================

// Filter 9: Merge Images --kholoud
void merge_images(Image &image1, Image &image2,int new_width, int new_height){

    Image merged_image(new_width, new_height);

    for (int i = 0; i < new_width; i++){
        for (int j = 0; j < new_height; j++){
            merged_image(i, j, 0) =(image1(i, j, 0) + image2(i, j, 0)) / 2;

            merged_image(i, j, 1) =(image1(i, j, 1) + image2(i, j, 1)) / 2;

            merged_image(i, j, 2) =(image1(i, j, 2) + image2(i, j, 2)) / 2;
        }
    }

image1 = merged_image;
}
// common area
void common_area_merge(Image &image1, Image &image2){
    int common_width = min(image1.width, image2.width);

    int common_height = min(image1.height, image2.height);

    Image merged_image(common_width, common_height);

    for (int i = 0; i < common_width; i++){
        for (int j = 0; j < common_height; j++){
            for (int k = 0; k < 3; k++){
                merged_image(i, j, k) =(image1(i, j, k)+image2(i, j, k)) / 2;
            }
        }
    }

    image1 = merged_image;
}

void resizing_images(Image &image1, Image &image2)
{
    //image 2 small
    if (image1.height * image1.width > image2.height * image2.width ){
        Image resized_image2(image1.width, image1.height);

        double ratio_w2 =double(image2.width) / image1.width;

        double ratio_h2 =double(image2.height) / image1.height;

        for (int i = 0; i < image1.width; i++){
            for (int j = 0; j < image1.height; j++){
                int old_width = i * ratio_w2;
                int old_height = j * ratio_h2;

                for (int k = 0; k < 3; k++){
                    resized_image2(i, j, k) =
                    image2(old_width, old_height, k);
                }
            }
        }
        image2 =resized_image2;
        merge_images(image1,image2,image1.width,image1.height);
    }
//image 1 small
    else if (image2.width * image2.height >image1.width * image1.height){
        Image resized_image1(image2.width, image2.height);

        double ratio_w1 =double(image1.width) / image2.width;

        double ratio_h1 =double(image1.height) / image2.height;

        for (int i = 0; i < image2.width; i++){
            for (int j = 0; j < image2.height; j++){
                int old_width = i * ratio_w1;
                int old_height = j * ratio_h1;

                for (int k = 0; k < 3; k++){
                    resized_image1(i, j, k) =
                    image1(old_width, old_height, k);
                }
            }
        }
        image1 =resized_image1;
        merge_images(image1,image2,image2.width,image2.height);
    }

    else if (image1.height == image2.height &&image2.width == image1.width){
         merge_images(image1,image2,image1.width,image1.height);
    }
    else{
        common_area_merge(image1, image2);
    }
}



//======================================================================================================

// Filter 10: Detect Image Edges --demiana
void detectEdges(Image& img, Image& newImg, int threshold) {

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            newImg.setPixel(i, j, 0, 255);
            newImg.setPixel(i, j, 1, 255);
            newImg.setPixel(i, j, 2, 255);
        }
    }

    Image gray(img.width, img.height);

    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {

            int r = img.getPixel(i, j, 0);
            int g = img.getPixel(i, j, 1);
            int b = img.getPixel(i, j, 2);

            int avg = (r + g + b) / 3;

            gray.setPixel(i, j, 0, avg);
        }
    }

    for (int x = 1; x < img.width - 1; x++) {
        for (int y = 1; y < img.height - 1; y++) {

            int gx =gray.getPixel(x + 1, y, 0) -gray.getPixel(x - 1, y, 0);

            int gy =gray.getPixel(x, y + 1, 0) -gray.getPixel(x, y - 1, 0);

            int val = sqrt(gx * gx + gy * gy);

            if (val > threshold) {
                newImg.setPixel(x, y, 0, 0);
                newImg.setPixel(x, y, 1, 0);
                newImg.setPixel(x, y, 2, 0);
            }
        }
    }
}

//=======================================================================================================

// Filter 11: Crop Images //youssef
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

//==========================================================================================================================

// Filter 12: Blur Images  --farha
void blur(Image& image) {

    Image oldimage = image;
    int level;
    cout << "Enter the level (1-3): ";
    cin >> level;
    while (cin.fail() || level < 1 || level > 3)
    {
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Invalid level. Enter a value from 1 to 3: ";
        cin >> level;
    }

    int r = 1;
    if(level == 1){
        r = 3;
    }
    else if(level == 2){
        r = 7;
    }
    else if(level == 3){
        r = 9;
    }

    for (int i = 0; i<image.width; i++){

        for(int j = 0; j<image.height; j++){

            int sumr = 0;
            int sumg = 0;
            int sumb = 0;
            int count = 0;

            for(int di = -r; di<=r; di++){

                for(int dj = -r; dj<=r; dj++){

                    int ni = i + di;
                    int nj = j + dj;

                    if(ni >= 0 &&ni < image.width &&nj >= 0 && nj < image.height){

                        sumr += oldimage(ni,nj,0);
                        sumg += oldimage(ni,nj,1);
                        sumb += oldimage(ni,nj,2);

                        count++;
                    }
                }
            }

            image(i,j,0) = sumr / count;
            image(i,j,1) = sumg / count;
            image(i,j,2) = sumb / count;
        }
    }
}
//==================================================================================================================
// Filter 13: Wano Sunlight Filter   ---- kholoud
void sun_light (Image & image) {
    for (int i = 0 ; i < image.width ; i++) {
        for (int j = 0 ; j < image.height ; j++) {
            image(i,j,0) = image(i,j,0)+(255-image(i,j,0))/2;
            image(i,j,1) = image(i,j,1)+(255-image(i,j,1))/2;
        }
    }
}

//==============================================================================================

// Filter 14: Old TV Effect  --demiana
void img_effect(Image& img) {

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {

            int r = img.getPixel(x, y, 0);
            int g = img.getPixel(x, y, 1);
            int b = img.getPixel(x, y, 2);

            if (y % 5 == 0 || y % 5 == 1 || y % 5 == 2) {
                r = r * 0.3;
                g = g * 0.3;
                b = b * 0.3;
            }

            img.setPixel(x, y, 0, r);
            img.setPixel(x, y, 1, g);
            img.setPixel(x, y, 2, b);
        }
    }

    int pp = (img.width * img.height) / 70;

    for (int i = 0; i < pp; i++) {

        int x = rand() % img.width;
        int y = rand() % img.height;

        img.setPixel(x, y, 0, 255);
        img.setPixel(x, y, 1, 255);
        img.setPixel(x, y, 2, 255);
    }
}

//==================================================================================

// Filter 15: Purple Filter --youssef
void purple_image(Image& image){
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            image(i, j, 0) = image(i, j, 0)*0.90;
            image(i, j, 1) = image(i, j, 1)*0.70;
        }
    }
}

//============================================================================

// Filter 16: Infrared Photography Filter  --farha
void infraredfilter(Image& old_photo){

    Image new_photo(old_photo.width, old_photo.height);

    for(int i = 0; i< old_photo.width; i++){
        for(int j = 0; j< old_photo.height; j++){

            unsigned char r = old_photo(i,j,0);

            new_photo(i,j,0) = 255;
            new_photo(i,j,1) = 255 -r ;
            new_photo(i,j,2) = 255 -r ;
        }
    }

    old_photo = new_photo;
}

//===============================================================================================================

// Filter 17: Image Skewing Filter --farha
Image skewing(Image& old, double angle){
    if (angle >= 89 || angle <= -89){
        return old;
    }

    double tan_value = tan(angle * 3.14159265 / 180.0);

    int max_shift = ceil(abs(old.height * tan_value));

    Image new_img(old.width + max_shift, old.height);


    for (int i = 0; i < new_img.height; i++){
        for (int j = 0; j < new_img.width; j++){
            for (int c = 0; c < 3; c++){
                new_img(j, i, c) = 255;
            }
        }
    }

    for (int i = 0; i < old.height; i++){
        int shift = round((old.height - 1 - i) * tan_value);

        if (tan_value < 0){
            shift += max_shift;
        }

        for (int j = 0; j < old.width; j++){
            for (int c = 0; c < 3; c++){
                new_img(j + shift, i, c) = old(j, i, c);
            }
        }
    }

    return new_img;
}

//=============================================================================================================================

// Filter 18: Oil Painting Filter --demiana
void oil(const Image& sourceImage, Image& outputImage, int radius, int levels) {

    int width = sourceImage.width;
    int height = sourceImage.height;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            vector<int> intensity(levels, 0);
            vector<int> sumR(levels, 0);
            vector<int> sumG(levels, 0);
            vector<int> sumB(levels, 0);

            for (int ny = -radius; ny <= radius; ++ny) {
                for (int nx = -radius; nx <= radius; ++nx) {

                    int currentX = x + nx;
                    int currentY = y + ny;

                    if (currentX >= 0 && currentX < width && currentY >= 0 && currentY < height) {

                        unsigned char r = sourceImage.getPixel(currentX, currentY, 0);

                        unsigned char g = sourceImage.getPixel(currentX, currentY, 1);

                        unsigned char b =sourceImage.getPixel(currentX, currentY, 2);

                        int currentIntensity =(r + g + b) / 3;

                        int intensityBin =(currentIntensity * levels) / 256;

                        if (intensityBin >= levels)
                            intensityBin = levels - 1;

                        intensity[intensityBin]++;

                        sumR[intensityBin] += r;
                        sumG[intensityBin] += g;
                        sumB[intensityBin] += b;
                    }
                }
            }

            int maxIndex = 0;
            int maxCount = 0;

            for (int i = 0; i < levels; ++i) {
                if (intensity[i] > maxCount) {
                    maxCount = intensity[i];
                    maxIndex = i;
                }
            }

            if (maxCount > 0) {

                unsigned char finalR =sumR[maxIndex] / maxCount;

                unsigned char finalG =sumG[maxIndex] / maxCount;

                unsigned char finalB =sumB[maxIndex] / maxCount;

                outputImage.setPixel(x, y, 0, finalR);
                outputImage.setPixel(x, y, 1, finalG);
                outputImage.setPixel(x, y, 2, finalB);
            }

            else {
                outputImage.setPixel(
                    x, y, 0,
                    sourceImage.getPixel(x, y, 0));

                outputImage.setPixel(
                    x, y, 1,
                    sourceImage.getPixel(x, y, 1));

                outputImage.setPixel(
                    x, y, 2,
                    sourceImage.getPixel(x, y, 2));
            }
        }
    }
}
//==================================================================================================
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
            cout << "Image saved." << endl;
            break;
        } catch (exception& e) {
            cout << e.what() << endl;
            cout << "Please try again." << endl;
        }
    }
}
//=================================================================================================

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
    cout << "9: Merge Images" << endl;
    cout << "10: Detect Edges" << endl;
    cout << "11: Crop Image" << endl;
    cout << "12: Blur Image" << endl;
    cout << "13: Wano Sunlight Filter" << endl;
    cout << "14: Old TV Effect" << endl;
    cout << "15: Purple Filter" << endl;
    cout << "16: Infrared Filter" << endl;
    cout << "17: Skew Image" << endl;
    cout << "18: Oil Painting Filter" << endl;
    cout << "19: Save Image" << endl;
    cout << "20: Exit" << endl;
    cout<<"choose from 0 to 20 :";

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
            while (true) {
                cout << "Save current image first? (y/n): ";
                cin >> answer;
                answer = tolower(answer);

                if (answer == 'y' || answer == 'n')
                    break;

            }
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

            while (true) {
                cin >> degree;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Please enter a number: ";
                    continue;
                }

                if (degree == 90 || degree == 180 || degree == 270)
                    break;

                cout << "Choose 90, 180, or 270 only: ";
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

        case 9: {
            Image image1 =image;
            Image image2;
            string file2;
            while (true) {
                cout << "Enter second image name: ";
                cin >> file2;

                try {
                    image2.loadNewImage(file2);
                    break;
                }
                catch(exception& e) {
                    cout << e.what() << endl;
                    cout << "Try again." << endl;
                }
            }

            int choice;
            cout << "1. Resize smaller image then merge"<<endl;
            cout << "2. Merge common area"<<endl;
            while (true) {
                cout << "Please choose 1 or 2 :";
                cin >> choice;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Please enter a number";
                    continue;
                }

                if (choice == 1 || choice == 2)
                    break;
                cout << "Invalid choice. Please choose 1 or 2." << endl;
            }


            if (choice == 1){
                resizing_images(image1, image2);
                image = image1;
            }
            else if (choice == 2){
                common_area_merge(image1, image2);
                image = image1;
            }
        break;
        }

        case 10: {
            Image edgeImg(image.width, image.height);
            detectEdges(image, edgeImg, 20);
            image = edgeImg;
            break;
        }

        case 11:
            crop_image(image);
            break;

        case 12:
            blur(image);
            break;

        case 13:
            sun_light(image);
            break;

        case 14:
            img_effect(image);
            break;

        case 15:
            purple_image(image);
            break;

        case 16:
            infraredfilter(image);
            break;

        case 17: {
            double angle;
            while (true) {
                cout << "Enter skew angle: ";
                cin >> angle;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Please enter a number";
                    continue;
                }

                if(angle >= 89 || angle <= -89) {
                    cout << "Angle must be between -89 and 89." << endl;

                }
                else {
                    image = skewing(image, angle);
                    break;
                }

            }
          break;
        }
        case 18: {
            int radius, levels;
                while (true) {
                    cout << "Please choose radius :";
                    cin >> radius ;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Please enter a number";
                        continue;
                    }
                    if (radius >=1 && radius <= 10)
                        break;

                    cout << "Radius must be between 1 and 10." << endl;
                }
            while (true) {
                cout << "Enter levels: ";
                cin >> levels;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Please enter a number";
                    continue;
                }

                if (levels<=3 && levels >=1)
                    break;

            cout<<"levels must between 1 and 3"<<endl;
            }

            Image output(image.width, image.height);
            oil(image, output, radius, levels);

            image = output;
            break;
        }

        case 19:
            saveCurrent(image, currentName);
            break;

        case 20: {
            char answer;
            while (true) {
                cout << "Save before exit? (y/n): ";
                cin >> answer;
                answer = tolower(answer);

                if (answer == 'y' || answer == 'n')
                    break;

            }

            if (answer == 'y')
                saveCurrent(image, currentName);

            return 0;
        }
        default:
            cout << "invalid choice" << endl;
            break;
    }

}
    return 0;
}