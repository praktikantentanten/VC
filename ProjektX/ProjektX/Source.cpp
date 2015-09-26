#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "Projektion.h"
#include "Speicher.h"




using namespace cv;
using namespace std;


int main(int argc, char *argv[])
{
		//Variablen für Test erzeugen
		Mat image = imread("adam1.png", 0);
		double alpha = 10;
		double beta = 90;
		double gamma =90; 
		double theta = 10;
		double phi = 90;
		Projektion Proj ;
		Speicher Speicher;
		Mat imageOut = image;
		Mathe Mathe;
		Mat winkels = (Mat_<double>(3, 2) << 60, 90,45,45,30,225);
		int i;
		/*
		for (i = 0; i <3;i++)
			Speicher.Save(Proj.bildRotieren(image, winkels.at<double>(i, 0), winkels.at<double>(i, 1)), image, "3Winkel", Mathe.WinkelZuString(winkels.at<double>(i, 0), winkels.at<double>(i, 1)));
		*/

		//bildnamen aus Parametern erstellen
		string s1 = Mathe.WinkelZuString(alpha, beta, gamma);
		string s2 = Mathe.WinkelZuString(theta, phi);
		string ad = "adam1";
		namedWindow("image");
		imshow("image", imageOut);
		waitKey(0);
		
		//bild erzeugen
		//imageOut = Proj.bildRotieren(image, alpha,beta,gamma);
		imageOut = Proj.bildRotieren(image, theta, phi);


		//Speichern
		Speicher.Save(imageOut, image,ad,s2);
	
				
		//extra Anzeige erzeugen und Bild darstellen
		namedWindow("image");
		imshow("image", imageOut);
		waitKey(0);			
		/*
		*/

}

