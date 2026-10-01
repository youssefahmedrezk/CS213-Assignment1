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
//================================================================================
//Farha part
void frame(Image& image){
   int choice;
    cout << "choose the frame"<<endl;
    cout<<"1 simple frame"<<endl;
    cout<<"2 fancy frame"<<endl;
    cin>>choice ;
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
    cout<<"enter the new width and height";
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

    switch (filter_num) {
        case 0: {
           char answer;
           cout << "Save the current image first? (y/n): ";
           cin >> answer;
           if (answer == 'y') {
               saveCurrent(image, currentName);
           }
           loadImage(image, currentName);
           break;
        } 
        case 1:
            gray_scale(image);
            saveCurrent(image, currentName);
            break;
        case 2:
            //black_and_white(image);
            break;
        case 3:
            invert_color(image);
            saveCurrent(image, currentName);
            break;
        case 4:
            frame(image);
            saveCurrent(image, currentName);
            break;
        case 5: {
            int mode;
            cout << "1: vertical, 2: horizontal: ";
            cin >> mode;
            if (mode == 1) vertical_image(image);
            else if (mode == 2) horizontal_image(image);
            else cout << "wrong mode" << endl;
            break;
        }
        case 6:
            //rotate_image(image);
            break;
        case 7: {
            int mode;
            cout << "1: lighten Image"<<endl;
            cout<<"2: Darken Image"<<endl;
            cout<<"please choose the mode: "<<endl;
            cin >> mode;
            lighten_darken(image, mode);
            saveCurrent(image, currentName);
            break;
        }
        case 8:
            applyresize(image);
            saveCurrent(image, currentName);
            break;
        case 9:
            saveCurrent(image, currentName);
            break;
        case 10:
            return 0;
        default:
            cout << "invalid choice" << endl;
    }
}
    return 0;
}
