#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "Image_Class.h"

using namespace std;


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
                        unsigned char b = sourceImage.getPixel(currentX, currentY, 2);

                        
                        int currentIntensity = (r + g + b) / 3;
                        int intensityBin = (currentIntensity * levels) / 256;

                        
                        if (intensityBin >= levels) intensityBin = levels - 1;

                        
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
                unsigned char finalR = sumR[maxIndex] / maxCount;
                unsigned char finalG = sumG[maxIndex] / maxCount;
                unsigned char finalB = sumB[maxIndex] / maxCount;

                outputImage.setPixel(x, y, 0, finalR);
                outputImage.setPixel(x, y, 1, finalG);
                outputImage.setPixel(x, y, 2, finalB);
            }
            else {
                outputImage.setPixel(x, y, 0, sourceImage.getPixel(x, y, 0));
                outputImage.setPixel(x, y, 1, sourceImage.getPixel(x, y, 1));
                outputImage.setPixel(x, y, 2, sourceImage.getPixel(x, y, 2));
            }
        }
    }
}

int main() {
    try {
        string inputPath, outputPath;
        cout << "Enter name image: ";
        cin >> inputPath;

        
        Image img(inputPath);

       
        Image outputImg(img.width, img.height);

        
        int radius =6;
        int levels = 10;

        oil(img, outputImg, radius, levels);

        cout << "Enter name image to save: ";
        cin >> outputPath;

        
        outputImg.saveImage(outputPath);
        cout << "DONE" << endl;

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}