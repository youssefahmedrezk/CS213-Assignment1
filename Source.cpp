#include <iostream>
#include <cmath>
#include "Image_Class.h"

using namespace std;


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
            int gx = gray.getPixel(x + 1, y, 0) - gray.getPixel(x - 1, y, 0);
            int gy = gray.getPixel(x, y + 1, 0) - gray.getPixel(x, y - 1, 0);

            int val = sqrt(gx * gx + gy * gy);

            if (val > threshold) {
                newImg.setPixel(x, y, 0, 0);
                newImg.setPixel(x, y, 1, 0);
                newImg.setPixel(x, y, 2, 0);
            }
        }
    }
}

int main() {
    string imageName;
    cout << "Enter image name: ";
    cin >> imageName;

    Image img(imageName);
    Image newImg(img.width, img.height);

    int threshold = 20;

   
    detectEdges(img, newImg, threshold);

    string saveName;
    cout << "Enter output image name: ";
    cin >> saveName;

    newImg.saveImage(saveName);
    cout << "Done!" << endl;

    return 0;
}