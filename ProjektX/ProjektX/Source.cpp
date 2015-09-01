#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "Projektion.h"




using namespace cv;
using namespace std;


int main(int argc, char *argv[])
{
		//Variablen f�r Test erzeugen
		Mat image = imread("adam1.png", 0);
		double alpha = 70;
		double beta = 90;
		double gamma = 90; 
		Projektion Proj ;
		Mat imageOut = image;
		
		//----------------------------------------------
		//bildnamen aus Parametern erstellen
		string a = to_string((int)alpha - 90);
		string b = to_string((int)beta - 90);
		string c = to_string((int)gamma - 90);
		string s;
		s = "adam " + a + " , " + b + " , " + c + ".png";
		
		//bild erzeugen
		imageOut = Proj.bildRotieren(image, alpha,beta,gamma);
				
		//bild speichern
		imwrite(s, imageOut);
				
		//extra Anzeige erzeugen und Bild darstellen
		namedWindow("image");
		imshow("image", imageOut);
		waitKey(0);			


}

