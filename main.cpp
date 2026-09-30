#include "Image_Class.h"
#include <iostream>
#include <string>
using namespace std;
//================================================================================
//youssef part
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
//==============================================================================
//kholoud part
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
int main() {
    Image image;
    cout << "Welcome to the Image Processing Program!" << endl;
    while(true) {
        cout << "Enter the name of the image file (with  validextension): ";
        string filename;
        cin >> filename;
        try {
            image.loadNewImage(filename);
            break;
        } catch (exception& e) {
            cout << e.what() << endl;
            cout << "Please try again." << endl;
        }
    }
    // khloud continue from here na duse while true to make sure the menu works inifnite until the user choose exit    
    return 0;
}