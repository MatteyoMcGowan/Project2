#include <iostream>
#include "E101.h"
#include <vector>
#include <cmath>

using namespace std;

// Constants
const int MIN_RED_PIXELS = 50;
const int MIN_TOTAL_COLOR = 60;
const float RED_COLOR_RATIO = 1.4f;
const int moveThreshold = 20;

// Helper function to check if a pixel is red
bool isRedPixel(int red, int green, int blue) {
    int total = red + green + blue;
    return total > MIN_TOTAL_COLOR && 
           red > green * RED_COLOR_RATIO && 
           red > blue * RED_COLOR_RATIO;
}

// Detects the red star and updates bounding box
bool detectRedRuby(int& top, int& bottom, int& left, int& right) {
    
    take_picture();

    int redPixelCount = 0;
    top = 240;
    bottom = 0;
    left = 320;
    right = 0;

    for (int row = 0; row < 240; row++) {
        for (int col = 0; col < 320; col++) {
            int red = (int)get_pixel(row, col, 0);
            int green = (int)get_pixel(row, col, 1);
            int blue = (int)get_pixel(row, col, 2);

            if (isRedPixel(red, green, blue)) {
                redPixelCount++;
                top = min(top, row);
                bottom = max(bottom, row);
                left = min(left, col);
                right = max(right, col);
            }
        }
    }

    return redPixelCount > MIN_RED_PIXELS;
}

      //crosshair at the center of the star
void drawCrosshair(int centerX, int centerY, int size, char r, char g, char b) {
    
    for (int col = centerX - size; col <= centerX + size; col++) {
        set_pixel(centerY, col, r, g, b);
    }
   
    for (int row = centerY - size; row <= centerY + size; row++) {
        set_pixel(row, centerX, r, g, b);
    }
}

int main() {
    int err = init(0);
    cout << "Init result: " << err << endl;
    
    open_screen_stream();

    int top, bottom, left, right;
    int refX = -1;
    int refY = -1;
    bool rubyDetectedInitially = false;

    while (true) {
        bool isFound = detectRedRuby(top, bottom, left, right);

        if (isFound) {
            int centerX = (left + right) / 2;
            int centerY = (top + bottom) / 2;

            if (!rubyDetectedInitially) {
                refX = centerX;
                refY = centerY;
                rubyDetectedInitially = true;
                cout << "Initial Ruby position set at (" << refX << ", " << refY << ")" << endl;
                set_digital(0, 0); // Turn off alert
            } else {
                int dx = abs(centerX - refX);
                int dy = abs(centerY - refY);

                if (dx > moveThreshold || dy > moveThreshold) {
                        cout << "ALERT: Red Ruby has moved!" << endl;
                        // drawRectangle(top, bottom, left, right, 255, 0, 0); // Red
                        drawCrosshair(centerX, centerY, 10, 255, 0, 0); // Red crosshair
                    
                } else {
                        cout << "Red Ruby is in place." << endl;
                        // drawRectangle(top, bottom, left, right, 0, 255, 0); // Green
                        drawCrosshair(centerX, centerY, 10, 0, 255, 0); // Green crosshair
					}
				}
			} 

            
        }

        update_screen(); 
        sleep1(500); 
    

    return 0;
}
