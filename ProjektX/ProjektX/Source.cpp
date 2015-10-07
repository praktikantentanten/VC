#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>
#include "Projektion.h"
#include "Speicher.h"
#include "KeyPointDetektor.h"




using namespace cv;
using namespace std;


int main(int argc, char *argv[])
{
		//Variablen für Test erzeugen
		Mat image = imread("adam1.png", 0);
		double alpha = 10; double beta = 90; double gamma =90; double theta = 10; double phi = 90;
		Projektion Proj; Speicher Speicher; Mat imageOut = image; Mathe Mathe; KeyPointDetektor KPDetek;
		Mat winkels = (Mat_<double>(3, 2) << 60, 90,45,45,30,225); // Mat für Winkel

		Mat img;													//Zwischenspeicher
		Mat coord1 =(Mat_ <double>(3,1) << 0, 0, 1);				//Zwischenspeicher
		Mat coord2;													//Zwischenspeicher
		vector<Mat> images;											//alle proj. Bildern
		vector<String>imagenName;									//Bildnamen von allen proj. Bildern
		vector<Projektion> imgProj;									//alle Projektion-Obj zu den proj. Bildern
		vector<Rect> bboxes;										//Die MSER-Bereiche fürs Ausschneiden
		int i; int w; int h; int k;									//Zählvariablen für Schleifen

		//bildnamen aus Parametern erstellen
		string s1 = Mathe.WinkelZuString(alpha, beta, gamma);
		string s2 = Mathe.WinkelZuString(theta, phi);
		string ad = "adam1";
		bboxes = KPDetek.Mser(image);
		//für jeden Winkel
		for (i = 0; i <winkels.size().height;i++)
		{
			//bilder drehen, wichtige Teile speichern
			images.push_back( Proj.bildRotieren(image, winkels.at<double>(i, 0), winkels.at<double>(i, 1)) );
			imgProj.push_back(Proj);
			imagenName.push_back(Mathe.WinkelZuString(winkels.at<double>(i, 0), winkels.at<double>(i, 1)));
		}
		//für jedes FeatureFeld
		for (i = 0; i < bboxes.size();i++)
		{
			ad =  to_string(i);
			//für jedes proj. Bild
			for (k = 0; k < images.size(); k++)
			{
				//Koordinaten Umrechnen				
				coord1 = (Mat_ <int>(3, 1) << bboxes.at(i).x, bboxes.at(i).y,  1);
				coord2 = (Mat_ <int>(3, 1) << bboxes.at(i).width, bboxes.at(i).height,  1);
				coord1 = imgProj.at(k).trans*coord1;
				coord2 = imgProj.at(k).trans*coord2;
				coord1.at<int>(0, 0) = coord1.at<int>(0, 0) / coord1.at<int>(2, 0);
				coord1.at<int>(1, 0) = coord1.at<int>(1, 0) / coord1.at<int>(2, 0);
				coord2.at<int>(0, 0) = coord2.at<int>(0, 0) / coord1.at<int>(2, 0);
				coord2.at<int>(1, 0) = coord2.at<int>(1, 0) / coord1.at<int>(2, 0);

				//Größe des Zwischenspeichers anpassen
				img.size() = images.at(k).size();
			
				//für jeden Punkt im FeatureFeld				
				for (w = coord1.at<int>(0,0); w < coord2.at<int>(0, 0); w++) //x-koordinate vom Ausschnitt
						for (h = coord1.at<int>(1, 0); h < coord2.at<int>(1, 0); h++)//y-koordinate vom Ausschnitt
						img.at<int>(h- coord1.at<int>(0, 0), w- coord1.at<int>(1, 0))=images.at(k).at<int>(h,w) ; //Zwischenspeicher befüllen von 0,0 an

				Speicher.Save(img,ad,imagenName.at(k)); //Abspeichern
				img.release(); //Zwischenspeicher leeren
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

