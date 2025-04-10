/*
 * The code below is meant to detect whether the Red Ruby
 * is present. The starategy implemented by the code is not very effective.
 * Study the code so that you understand what the strategy is and how
 * it is implemented. Then design and implement a better startegy.
 *
 * */



#include <iostream>
#include "E101.h"

using namespace std;

int main()
{
	int err = init(0);
	cout<<" Hello. err="<<err<<endl;
	int redpixel = 0; // for each individual pixels in the  image.
	int greenpixel = 0;
	int bluepixel = 0;
	
	//bool check_red = false; // check if there is more red pixels than green or blue pixels
	int redpixelcount = 0;
	int nonredpixelcount = 0;
	open_screen_stream();


  // make 1000 runs
  for(int countrun =0; countrun <1000; countrun=countrun+1)
  {
	take_picture();
	redpixelcount =0;
	nonredpixelcount = 0;
    redpixel = 0;
    greenpixel = 0;
    bluepixel = 0;

    // for all pixels in latest image
    for ( int row = 0 ; row <240 ; row=row+1)
	{
		for (int col=0; col<320; col=col+1)
		{
            //0 red, 1 green, 2 blue, 3 grayscale (all three colours divided by 3).
			redpixel = (int)get_pixel(row,col,0);
			greenpixel = (int)get_pixel(row,col,1);
			bluepixel = (int)get_pixel(row,col,2);
	
		
			if(redpixel > 2*greenpixel && redpixel > 2*bluepixel){
				redpixelcount++;
				set_pixel(row,col,255,0,0);
			}
			else{
				nonredpixelcount++;
				set_pixel(row,col,255,255,255);				
			}
		}
	}
	update_screen();
	//cout<<redpixelcount<<endl;
	//cout<<nonredpixelcount<<endl;
	
	if (redpixelcount > 3500){
		//cout<<"Ruby is present"<<endl;
	}
	else if (redpixelcount >= 2500){
		//cout<<"CAUTION: Stealing in progress!"<<endl;
	}
	else if(redpixelcount <= 1250 ){
		sleep1(2000); // slow down a bit to make display easier
		cout<<"WARNING: The ruby has been stolen!"<<endl;
		break;
	}
	
  }
  
  close_screen_stream();
  return 0;
}
