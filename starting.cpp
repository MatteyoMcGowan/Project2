/*
 * The code below is meant to detect whether the Red Ruby
 * is present. The starategy implemented by the code is not very effective. 
 * Study the code so that you understand what the strategy is and how 
 * it is implemented. Then design and implement a better startegy.
 * 
 * */
#include <iostream>
#include "E101.h"
#include <vector>

using namespace std;

bool detectRedRuby(int& top, int& bottom, int& left, int& right) {
    int numPixels = 240 * 320;
    int redThreshold = 0;
    int avgBrightness = 0;
    int totalRed = 0;
    int totalGreen = 0;
    int totalBlue = 0;
    int totalBrightness = 0;
    int redPixelCount = 0;

    take_picture();  

 
    for (int row = 0; row < 240; row++) {    
        for (int col = 0; col < 320; col++) {
            int red = (int)get_pixel(row, col, 0);
            int green = (int)get_pixel(row, col, 1);
            int blue = (int)get_pixel(row, col, 2);

            totalRed += red;
            totalGreen += green;
            totalBlue += blue;
            totalBrightness += (red + green + blue) / 3;

           
            if (red > redThreshold && green < 100 && blue < 100) {
                redPixelCount++;
                if (top > row) top = row;
                if (bottom < row) bottom = row; 
                if (left > col) left = col;
                if (right < col) right = col;
            }
        }
    }

    // If any red pixels are found, calculate dynamic redThreshold
    if (redPixelCount > 0) {
        avgBrightness = totalBrightness / numPixels;
        int avgRed = totalRed / redPixelCount;

        
        redThreshold = avgRed * 1.2; 
        redThreshold = redThreshold * (avgBrightness / 128);  // Adjust based on brightness
        return true;  // Red Ruby found
    }

    return false;  
}

int main() {
    int err = init(0);
    cout << "Error: " << err << endl;
    open_screen_stream();

    int top = 240;
    int bottom = 0;
    int left = 320;
    int right = 0;

    while (true) {
        bool isFound = detectRedRuby(top, bottom, left, right);

        if (isFound) {
            cout << "Red Ruby Found!" << endl;
            cout << "Top: " << top << ", Bottom: " << bottom << ", Left: " << left << ", Right: " << right << endl;
        } else {
            cout << "Red Ruby Not Found!" << endl;
        }
		sleep1(500);
    }

    return 0;
}
