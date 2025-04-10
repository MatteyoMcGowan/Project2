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

int main() {
    int err = init(0);
    cout << "Error: " << err << endl;
    open_screen_stream();
  
    Startup();
  
    return 0;
}

void Startup() { 
    int top = 240;
    int bottom = 0;
    int left = 320;
    int right = 0;
    int numPixels = 240 * 320;
    int redThreshold = 0;
    int avgBrightness = 0;
    
    for (int startUp = 0; startUp < 2; startUp++) {
        take_picture();
        
        int totalRed = 0;  
        int totalGreen = 0; 
        int totalBlue = 0; 
        int totalBrightness = 0;
        int redPixelCount = 0;

        // Scan the image to compute the necessary statistics
        for (int row = 0; row < 240; row++) {    
            for (int col = 0; col < 320; col++) {
                int red = (int)get_pixel(row, col, 0);
                int green = (int)get_pixel(row, col, 1);
                int blue = (int)get_pixel(row, col, 2);

                totalRed += red;
                totalGreen += green;
                totalBlue += blue;
                totalBrightness += (red + green + blue) / 3;
                
                // Count red pixels and update bounding box
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
            
            // Adjust the threshold dynamically based on image characteristics
            redThreshold = avgRed * 1.2;  // Increase threshold by a factor of 1.2 for robustness
            redThreshold = redThreshold * (avgBrightness / 128);  // Adjust based on brightness
        } else {
            redThreshold = 0;  // No red pixels found, set threshold to 0
        }

        // Print out bounding box if red pixels were found
        if (redPixelCount > 0) {
            cout << "Red Ruby Found!" << endl;
            cout << "Top: " << top << ", Bottom: " << bottom << ", Left: " << left << ", Right: " << right << endl;
        } else {
            cout << "Red Ruby Not Found!" << endl;
        }
    }
}


