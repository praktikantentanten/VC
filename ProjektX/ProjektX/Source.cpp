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
		Projektion Proj; Speicher Speicher; Mat imageOut = image; Mathe Mathe;
		Mat winkels = (Mat_<double>(3, 2) << 0, 0,45,45,30,225); // Mat für Winkel

		Mat img;													//Zwischenspeicher
		Mat coord1 =(Mat_ <double>(3,1) << 0, 0, 1);				//Zwischenspeicher
		Mat coord2 = (Mat_ <double>(3, 1) << 0, 0, 1);				//Zwischenspeicher
		Mat coord3 = (Mat_ <double>(3, 1) << 0, 0, 1);				//Zwischenspeicher
		Mat coord4 = (Mat_ <double>(3, 1) << 0, 0, 1);				//Zwischenspeicher
		vector<double> coordZ;										//Zwischenspeicher
		vector<Mat> images;											//alle proj. Bildern
		vector<String>imagenName;									//Bildnamen von allen proj. Bildern
		vector<Projektion> imgProj;									//alle Projektion-Obj zu den proj. Bildern		
		int i; int w; int h; int k;									//Zählvariablen für Schleifen

		//bildnamen aus Parametern erstellen
		string s1 = Mathe.WinkelZuString(alpha, beta, gamma);
		string s2 = Mathe.WinkelZuString(theta, phi);
		string ad = "adam1";
		/// fehler:
		Ptr<cv::MSER> mser = MSER::create();
		vector< vector<Point > > ptblobs;
		vector<Rect> bboxes;
		//MSER Detect wird ausgeführt 
		mser->detectRegions(image, ptblobs, bboxes);

		//für jeden Winkel
		for (i = 0; i <winkels.size().height;i++)
		{
			//bilder drehen, wichtige Teile speichern
			images.push_back( Proj.bildRotieren(image, winkels.at<double>(i, 0), winkels.at<double>(i, 1)) );
			imgProj.push_back(Proj);
			imagenName.push_back(Mathe.WinkelZuString(winkels.at<double>(i, 0), winkels.at<double>(i, 1)));
			Speicher.Save(images.at(i), "testo", imagenName.at(i)); //Abspeichern
		}
		//für jedes FeatureFeld
		for (i = 0; i < bboxes.size();i++)
		{
			ad =  to_string(i);
			//für jedes proj. Bild
			for (k = 0; k < images.size(); k++)
			{
				
				cout << "Koordinaten Umrechnen " << k << "_" << i << endl;
				std::cout << std::endl;
				coord1 = (Mat_ <double>(3, 1) << bboxes.at(i).x, bboxes.at(i).y,  1);
				cout << "coord1 vor trans " << coord1.at<int>(0, 0) << " _ " << coord1.at<int>(1, 0) << " _ " << coord1.at<int>(2, 0) << endl;
				coord2 = (Mat_ <double>(3, 1) << bboxes.at(i).x , bboxes.at(i).y + bboxes.at(i).height,  1);
				coord3 = (Mat_ <double>(3, 1) << bboxes.at(i).x + bboxes.at(i).width, bboxes.at(i).y, 1);
				coord4 = (Mat_ <double>(3, 1) << bboxes.at(i).x + bboxes.at(i).width, bboxes.at(i).y + bboxes.at(i).height, 1);
				coordZ = imgProj.at(k).sizeBerechnen(coord1, coord2, coord3, coord4, imgProj.at(k).trans);
				cout << "coord1 nach trans " << coord1.at<int>(0, 0) << " _ " << coord1.at<int>(1, 0) << " _ " << coord1.at<int>(2, 0) << endl;
				std::cout << std::endl;
				//neuen 0-Punkt berechnen
				coord2.at<int>(0, 0) = 0;
				coord2.at<int>(1, 0) = 0;
				coord2.at<int>(2, 0) = 1;
				coord2 = imgProj.at(k).trans*coord2;
				//durch z teilen
				coord2.at<int>(0, 0) = coord2.at<int>(0, 0) / coord2.at<int>(2, 0);
				coord2.at<int>(1, 0) = coord2.at<int>(1, 0) / coord2.at<int>(2, 0);
				//0-Punkt addieren
				coord1.at<int>(0, 0) = coord1.at<int>(0, 0) - coord2.at<int>(0, 0);
				coord1.at<int>(1, 0) = coord1.at<int>(1, 0) + coord2.at<int>(1, 0);
				//Maximalwerte einspeichern
				coord4.at<int>(0, 0) = coordZ.at(0);
				coord4.at<int>(1, 0) = coordZ.at(1);

				cout << "Bildpunkte:coord1 " << coord1.at<int>(0, 0) << " _ " << coord1.at<int>(1, 0) << " _ " << coord1.at<int>(2, 0) 
					 << "Bildpunkte:coord2 " << coord2.at<int>(0, 0) << " _ " << coord2.at<int>(1, 0) << " _ " << coord2.at<int>(2, 0)
					 << "Bildpunkte:coord4 " << coord4.at<int>(0, 0) << " _ " << coord4.at<int>(1, 0) << endl;
				std::cout << std::endl;
				cout << "Groeße des Zwischenspeichers anpassen" << endl;
				img = Mat::zeros(coord4.at<int>(0,0), coord4.at<int>(1, 0) , CV_64F );
			
				cout << "fuer jeden Punkt im FeatureFeld" << endl;
				std::cout << std::endl;
				for (w = coord1.at<int>(0,0); w < coord4.at<int>(0, 0); w++) //x-koordinate vom Ausschnitt
				{
					cout << "Bildpunkt w,h0: (" << w << "," << coord1.at<int>(1, 0) << "): " << images.at(k).at<int>(w, coord1.at<int>(1, 0)) << endl;
					for (h = coord1.at<int>(1, 0); h < coord4.at<int>(1, 0); h++)//y-koordinate vom Ausschnitt
						img.at<int>(w - coord1.at<int>(0, 0), h - coord1.at<int>(1, 0)) = images.at(k).at<int>(w, h); //Zwischenspeicher befüllen von 0,0 an
					
				}
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

