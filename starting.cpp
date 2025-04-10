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
  cout<<"Error: "<<err<<endl;
  open_screen_stream();

  int top = 240;
  int bottom = 0;
  int left = 320;
  int right = 0;
  
  int totalRed = 0;
  int numPixels = 240 * 320;
  
  struct Points 
  {
	  int row;
	  int col;
  };
  vector<Points> redPixelsLoc;
  
  
  for (int row = 0; row < 240; row++) {
     for (int col = 0; col < 320; col++) {
       int red = (int)get_pixel(row, col, 0);
       totalRed += red;
   }
}
    int avgRed = totalRed / numPixels;

    int redThreshold = avgRed * 1.2;

  for (int startUp = 0; startUp < 2; startUp++){
	  take_picture();
	  for (int row = 0 ; row < 240 ; row++) {	
		for (int col = 0; col < 320; col++) {
			int red =   (int)get_pixel(row, col, 0);
			int green = (int)get_pixel(row, col, 1);
			int blue =  (int)get_pixel(row, col, 2);
			
			if (red > redThreshold && green < 100 && blue < 100){
				redPixelsLoc.push_back({row, col});
				}	
			}

	for(size_t i = 0; i < redPixelsLoc.size(); i++){
		int row = redPixelsLoc[i].row;  
        int col = redPixelsLoc[i].col;
        
		if (top > row) top = row;
		if (bottom < row) bottom = row; 
		if (left > col) left = col;
		if (right < col) right = col;
		}
	}
  }
}

  /*
  // make 1000 runs  
  for (int countrun = 0; countrun < 1000; countrun++) {
	take_picture();
	update_screen();
	int totRed = 0;
	int totInt = 0;
	double redness = 0.0;
	int middleRed = 0;
	int middleGreen = 0;
	int middleBlue = 0;
    // for all pixels in latest image
    for (int row = 0 ; row < 240 ; row++) {	
		for (int col = 0; col < 320; col++) {
			totRed = totRed + (int)get_pixel(row, col, 0);
			totInt = totInt + (int)get_pixel(row, col, 3);
			redness = (double)totRed/(3.0*(double)totInt);
			
			if (row > 110 && row < 140 && col > 150 && col < 170){
				middleRed = (int)get_pixel(row, col, 0);
				middleGreen = (int)get_pixel(row, col, 1);
				middleBlue = (int)get_pixel(row, col, 2);
				}
			

		}
	}
	
	cout<<" countrun: "<<countrun<<endl<<endl;
	cout<<" Total red: "<<totRed<<endl;
	cout<<", Total intensity: "<<totInt<<endl;
	cout<<", redness : "<<redness<<endl<<endl;
	cout<<", Middle Red: "<<middleRed<<endl<<endl;
	cout<<", Middle Green: "<<middleGreen<<endl<<endl;
	cout<<", Middle Blue: "<<middleBlue<<endl<<endl;
	
	if (middleRed < 140){
		cout<<"THE RUBY HAS BEEN STOLEN"<<endl;
	}else {
		cout<<"The Ruby is safe..."<<endl;
		} 
				
	
	sleep1(500); // slow down a bit to make display easier 2fps
	
  }  
  close_screen_stream();
  return 0;
} */
