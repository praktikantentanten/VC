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
		/*
		adam 0 , 20 , 0 _ 22, 31
		adam 0 , -20 , 0 _ -60, 31
		adam 5 , 0 , 0 _ 8, 5
		adam -5 , 0 , 0 _ 8, -7
		adam 10 , 0 , 0 _ 15, 8
		adam -10 , 0 , 0 _ 15, -15
		adam 20 , 0 , 0 _ 30, 9
		adam -20 , 0 , 0 _ 30, -37

			*/
		//----------------------------------------------
		//bildnamen aus Parametern erstellen
		string a = to_string((int)alpha - 90);
		string b = to_string((int)beta - 90);
		string c = to_string((int)gamma - 90);
		string t = to_string((int)theta);
		string p = to_string((int)phi);
		string s;
		string s1;
		s1 = "adam " + a + " , " + b + " , " + c + ".png";
		s = "kugel " + t + " _ " + p + ".png";
		//bild erzeugen
		//imageOut = Proj.bildRotieren(image, alpha,beta,gamma);
		imageOut = Proj.bildRotieren(image, theta, phi);

		//Ordner erstellen bzw auswählen
		Speicher.SetFolder(s);

		//bild speichern
		imwrite(s, imageOut);
				
		//extra Anzeige erzeugen und Bild darstellen
		namedWindow("image");
		imshow("image", imageOut);
		waitKey(0);			


}

