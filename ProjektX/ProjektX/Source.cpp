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
		int ar = 3;
		Mat img;
		vector<Mat> images;
		vector<String>imagenName;
		vector<Mat> transMs;
		vector<Rect> bboxes;
		int i; int j; int h; int k;

		//bildnamen aus Parametern erstellen
		string s1 = Mathe.WinkelZuString(alpha, beta, gamma);
		string s2 = Mathe.WinkelZuString(theta, phi);
		string ad = "adam1";

		//für jeden Winkel
		for (i = 0; i <winkels.size().height;i++)
		{
			//bilder drehen
			images.push_back( Proj.bildRotieren(image, winkels.at<double>(i, 0), winkels.at<double>(i, 1)) );
			imagenName.push_back(Mathe.WinkelZuString(winkels.at<double>(i, 0), winkels.at<double>(i, 1)));
		}
		//für jedes FeatureFeld
		for (i = 0; i < bboxes.size;i++)
		{
			ad =  to_string(i);
			//für jedes proj. Bild
			for (k = 0; k < images.size; k++)
			{
/* TRANSFORMATIONSMATRIX MUSS NOCH VERWENDET WERDEN
----------------------------------------------------------------------------------------------------------------------+++++++++++gerhroghrgherg
				*/
				img.size() = images.at(k).size(); //Größe des Zwischenspeichers anpassen
				//für jeden Punkt im FeatureFeld
				for (h = bboxes.at(i).x; h < bboxes.at(i).height; h++)
					for (j = bboxes.at(i).y; j < bboxes.at(i).width; j++)
						img.at<int>(h- bboxes.at(i).x, h-bboxes.at(i).y)=images.at(k).at<int>(h,j) ;
				Speicher.Save(img,ad,imagenName.at(k)); //Abspeichern
				img.release; //Zwischenspeicher leeren
			}
		}


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

