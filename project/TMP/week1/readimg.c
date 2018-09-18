#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>

int main()
{
	cvNamedWindow( "result", 1 );

	const char* p_name[4];// = new char[4];
	p_name[0]="01.jpg";
        p_name[1]="02.jpg";
	p_name[2]="03.jpg";
        p_name[3]="04.jpg";

	int i=0;
	int bound = 10;
     	while(i<bound)
     	{
		int y = i%4;

		IplImage *img=cvLoadImage(p_name[y]);

		cvShowImage( "result", img );

		// Show the image in the window named "result"
	    	cvShowImage( "result", img );
		
		cvWaitKey(2000);
		cvReleaseImage(&img);
		i++;
     	}   

     	cvDestroyWindow("result");			
     	return 0;
}
