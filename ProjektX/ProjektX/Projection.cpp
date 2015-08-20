#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "BildSchneiden.h"
#include "Projektion.h"




using namespace cv;
using namespace std;


int main(int argc, char *argv[])
{

		Mat image = imread("adam1.png", 0);
		double alpha = 90; double beta = 90; double gamma = 90; double dx = 90; double dy = 90; double dz = 90;
		Mat imageOut = Projektion::change(image);
		

		string a = to_string((int)alpha - 90);
		string b = to_string((int)beta - 90);
		string c = to_string((int)gamma - 90);
	
		string s;
		string dxs = to_string((int)dx);
		string dys = to_string((int)dy);
		string dzs = to_string((int)dz);

		s ="adam "+a + " , " +b + " , " +c + " _ " + dxs+ " , " + dys + " , "+ " , " + dzs +  ".png";
		
		

		IplImage imageA = imread("adam1.png");
		CvRect imageB ;
		BildSchneiden cImage;
		cImage.cropImage(&imageA, imageB);

		imwrite(s, imageOut);
		namedWindow("image");
		imshow("image", imageOut);
		waitKey(0);

}

