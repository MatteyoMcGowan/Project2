#include <iostream>
#include "E101.h"
#include <vector>
#include <cmath>

using namespace std;

const int MIN_RED_PIXELS = 50;
const int MIN_TOTAL_COLOR = 60;
const float redColorRatio = 1.4f; // typically to be red it must be 40% more red than green or blue
const int moveThreshold = 20;

// pixel is red ?
bool isRedPixel(int red, int green, int blue) {
    int total = red + green + blue;
    return total > MIN_TOTAL_COLOR && 
           red > green * redColorRatio && 
           red > blue * redColorRatio;
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


/* Opens stream
 * sets variables and ruby to false
 * while(true) infinate loop
 * if ruby isfound by detectRedRuby 
 * set if (isfound) will = true
 * intilises the center
 * set centerX/y = ref x/y 
 * second loop around dx dy to see if there is any changes
 * if the abs value goes above 20
 * ruby stolen
 * else fine
 */


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
		
	    // calculates center 
        if (isFound) {
            int centerX = (left + right) / 2;
            int centerY = (top + bottom) / 2;
			
            if (!rubyDetectedInitially) {
                refX = centerX;
                refY = centerY;
                rubyDetectedInitially = true;
                cout << "Initial Ruby position set at (" << refX << ", " << refY << ")" << endl;
            } else {
                int dx = abs(centerX - refX);
                int dy = abs(centerY - refY);

                if (dx > moveThreshold || dy > moveThreshold) {
                        cout << "The red ruby has been moved" << endl;
                       
                        drawCrosshair(centerX, centerY, 10, 255, 0, 0); // Red crosshair (stolen)
                    
                } else {
                        cout << "The red ruby is safe..." << endl;
                     
                        drawCrosshair(centerX, centerY, 10, 0, 255, 0); // Green crosshair (fine)
					}
				}
			} 

            
        }

        update_screen(); 
        sleep1(500); 
    

    return 0;
}
