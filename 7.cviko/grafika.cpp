//#include "stdafx.h"
#include <math.h> 
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat mojeFunkce(Mat image, Mat kernelX, Mat kernelY)
{
    Mat output(image.rows,image.cols, CV_8UC1, Scalar(0));
    for( int y = 1; y < image.rows; y++ )
    { 
        for( int x = 1; x < image.cols - 1; x++ )
        {
			for (int j = 1; j < image.rows; j++) {
				output.at<unsigned char>(y, x) = 255 - image.at<unsigned char>(y, x);
			}
			
			//cout << CV_8UC1;
			// urobim absolutnu hodnotu..
			//if (output.at<unsigned char>(y, x) < 0) {
			//	abs(output.at<unsigned char>(y, x));
			//}
			//else {
			//	
			//}
			
			// interval od <0 , 255>
			// absolutnu z x 
			// ak orez tak minimum alebo maximum
			
			//max(min, (x, 255), 0);
        }
    }
    return output;
}



int main(int argc, char* argv[])
{
    cout << "Ahoj svete" << endl;
    
    Mat image;
    image = imread("Lena.jpg", CV_LOAD_IMAGE_COLOR);  

    // 2x2 cerveny obrazek
    Mat M(2,2, CV_8UC3, Scalar(0, 0, 255));
    cout << "M = " << endl << " " << M << endl << endl;

    imwrite( "image1_2x2_cervena.bmp", M );     

    // nova matice
    Mat gray_image(image.rows , image.cols, CV_8UC1);
    // konvert do sede
    cvtColor( image, gray_image, CV_BGR2GRAY );
    
    // pridame caru
    line(image, Point(10, 10), Point(100, 100), Scalar(124, 51, 210), 1, 8, 0);
    // pridame kolecko
    circle(image, Point(100, 200), 50, Scalar(202, 0, 54), 1, 8, 0);
    // a jeste to popiseme
    putText(image,"Ahoj svete", Point(100,100), CV_FONT_HERSHEY_COMPLEX, 0.5, Scalar(0,158,112),1,8,0);

    // a vrazime tam zelenej pixel
    image.at<Vec3b>(20, 5)[0] = 0;
    image.at<Vec3b>(20, 5)[1] = 255;
    image.at<Vec3b>(20, 5)[2] = 0;

    imwrite("image2_pocmarana_lena.bmp", image);

    double alpha = 3.0;
    int beta = 0;
    Mat new_image(image.rows , image.cols, CV_8UC3);
    for( int y = 0; y < image.rows; y++ )
    { 
        for( int x = 0; x < image.cols; x++ )
        { 
            for( int c = 0; c < 3; c++ )
            {
                new_image.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( alpha*( image.at<Vec3b>(y,x)[c] ) + beta );
            }
        }
    }
  
    imwrite("image3_saturace.bmp", new_image);  

    
    Mat sobelA = (Mat_<int>(3, 3) << 1, 0, -1,
                                     2, 0, -2, 
                                     1, 0, -1); 
    Mat sobelB = (Mat_<int>(3, 3) << 1, 2, 1,
                                     0, 0, 0, 
                                    -1, -2, -1); 
                                    
                                     
    Mat testImage = (Mat_<uchar>(3, 3) << 1, 2, 3,
                                          4, 5, 6, 
                                          7, 8, 9);                                      
 
    cout << "sobelA = " << endl << " " << sobelA << endl << endl;

  
    Mat output_x;
    Mat output_y;
  
    //Sobel(vstup , vystup, barvy, X, Y, velikost matice);
    Sobel(gray_image, output_x, CV_8U, 1, 0, 3);
    Sobel(gray_image, output_y, CV_8U, 0, 1, 3);
    imwrite("sobelOpenCV_X.bmp", output_x); 
    imwrite("sobelOpenCV_Y.bmp", output_y); 
  
    Mat output_my;
    output_my = mojeFunkce(gray_image, sobelA, sobelB);
    imwrite("my_sobel.bmp", output_my); 
   

    
//    waitKey(0);
    return 0;
}

