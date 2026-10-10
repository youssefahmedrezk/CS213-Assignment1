#include <iostream>
#include "Image_Class.h"
#include <cstdlib>

using namespace std;


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

int main() {
    string imageName;
    cout << "Enter image name: ";
    cin >> imageName;

    Image img(imageName);

    img_effect(img);

    string saveName;
    cout << "Enter output image name: ";
    cin >> saveName;

    img.saveImage(saveName);
    cout << "Done!" << endl;

    return 0;
}