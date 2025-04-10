#include <iostream>
#include "E101.h"
#include <vector>
#include <cmath>

using namespace std;

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
            int total = red + green + blue;

            // changes depending on lights levels
            if (total > 60 && red > green * 1.4 && red > blue * 1.4) {
                redPixelCount++;

                if (row < top) top = row;
                if (row > bottom) bottom = row;
                if (col < left) left = col;
                if (col > right) right = col;
            }
        }
    }

    return redPixelCount > 50;  // Avoid false positives
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
                cout << "Initial Ruby position set at (" << refX << ", " << refY << ")" << endl; // midddle of star
                set_digital(0, 0); // Turn off alert
            } else {
                int dx = abs(centerX - refX);
                int dy = abs(centerY - refY);

                if (dx > 20 || dy > 20) {
                    cout << "Ruby stolen!" << endl;
                    set_digital(0, 1); // Turn on alert
                } else {
                    cout << "The precious is safe..." << endl;
                    set_digital(0, 0); // Turn off alert
                }
            }

            cout << "Top: " << top << ", Bottom: " << bottom 
                 << ", Left: " << left << ", Right: " << right << endl;
        } else {
            cout << "Red Ruby not found!" << endl;
            if (rubyDetectedInitially) {
                cout << "ALERT: Red Ruby possibly stolen!" << endl;
                set_digital(0, 1); // Turn on alert
            } else {
                set_digital(0, 0); // No alert yet
            }
        }

        sleep1(500); // wait 500ms
    }

    return 0;
}
