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
                else{
                cout<<"wrong mode"<<endl;}
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
        cout << "Enter the name of the image file (with valid extension): ";
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
cout<<"-------------please enter filter number (choose from 1:8)--------------------------";
    cout << "Filter 1: Grayscale Conversion"<<endl;
    cout << "Filter 2: Black and White"<<endl;
    cout << "Filter 3: Invert Image"<<endl;
    cout << "Filter 4: Adding a Frame"<<endl;
    cout << "Filter 5: Flip Image"<<endl;
    cout<<"Filter 6: Rotate Image"<<endl;
    cout<<"Filter 7: Darken and Lighten Image"<<endl;
    cout<<"Filter 8: Resizing Images"<<endl;

    int filter_num;
    cin >> filter_num;
    switch(filter_num) {
        case 1:
            gray_scale(image);
            break;
        case 2:
            // black_and_white(image);
            break;
        case 3:
            invert_color(image);
            break;
        case 4:
            // add_frame(image);
            break;
        case 5:
            cout<<"enter flipped mode";
            int mode;
            cin>>mode;
            if (mode==1) {
                vertical_image(image);
            }
            else if (mode==2) {
                horizontal_image(image);
            }
            else {
                cout<<"wrong mode"<<endl;
            }
            break;
        case 6 :
            //rotate_image(image);
            break;
        case 7:
            cout<<"1 : darken"<<endl;
            cout<<"2 : lighten"<<endl;
            cout<<"choose number of the mode"<<endl;
            int mode;
            cin>>mode;
            lighten_darken(image,mode);
            break;
        case 8 :
            //resize_image(image);
            break;
    }


    return 0;
}