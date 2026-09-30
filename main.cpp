#include "Image_Class.h"
#include <iostream>
#include <string>
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

void lighten_darken(Image& image,string mode) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {
                if (mode == "lighten")
                {
                    image(i,j,k) = image(i,j,k)+(255-image(i,j,k))/2;
                }
                if (mode == "darken")
                {
                    image(i,j,k) = image(i,j,k)/2;
                }                
            }
        }
    }
}
int main() {
    Image image("luffy.jpg");
    string mode;
    invert_color(image);
    image.saveImage("new1.jpg");
    image.loadNewImage("luffy.jpg");
    cout << "Type lighten or darken: ";
    cin >> mode;
    lighten_darken(image, mode);   
    image.saveImage("new.jpg");
    return 0;
}