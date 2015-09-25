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
		double theta = 15;
		double phi = 90;
		Projektion Proj ;
		Speicher Speicher;
		Mat imageOut = image;

		//bildnamen aus Parametern erstellen
		string a = to_string((int)alpha - 90);
		string b = to_string((int)beta - 90);
		string c = to_string((int)gamma - 90);
		string t = to_string((int)theta);
		string p = to_string((int)phi);
		string s;
		string s1;
		string ad = "adam1";
		s1 = "adam " + a + " , " + b + " , " + c;
		s = "kugel " + t + " _ " + p;
		//bild erzeugen
		//imageOut = Proj.bildRotieren(image, alpha,beta,gamma);
		imageOut = Proj.bildRotieren(image, theta, phi);


		//Speichern
		Speicher.Save(imageOut, image,ad,s);
	


				
		//extra Anzeige erzeugen und Bild darstellen
		namedWindow("image");
		imshow("image", imageOut);
		waitKey(0);			


}

