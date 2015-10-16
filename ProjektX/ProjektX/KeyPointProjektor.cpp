#include "KeyPointProjektor.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "Projektion.h"
#include "Speicher.h"

using namespace cv;
using namespace std;


KeyPointProjektor::KeyPointProjektor()
{
}


KeyPointProjektor::~KeyPointProjektor()
{
}

/* Übergeben werden muss:
vector<Rect> bboxes;
Mat coordZ = imgProj.at(k).sizeBerechnen(coord1, coord2, coord3, coord4, imgProj.at(k).trans);

*/
 bool KeyPointProjektor::keyPointsProj(vector<Rect> boxes, vector<double> coordZ, Mat trans,Mat image,string name)
{
	string ad = "";
	Mat img;int i; int w; int h;
	Speicher Speicher;
	bboxes = boxes;
	//für jedes FeatureFeld
	for (i = 0; i < bboxes.size(); i++)
	{
		ad = "k"+to_string(i);
		

		cout << "KeypointNr:"   << i << endl;
		std::cout << std::endl;
		Mat coord1 = (Mat_ <double>(3, 1) << bboxes.at(i).x, bboxes.at(i).y, 1);
		Mat coord2 = (Mat_ <double>(3, 1) << bboxes.at(i).x, bboxes.at(i).y + bboxes.at(i).height, 1);
		Mat coord3 = (Mat_ <double>(3, 1) << bboxes.at(i).x + bboxes.at(i).width, bboxes.at(i).y, 1);
		Mat coord4 = (Mat_ <double>(3, 1) << bboxes.at(i).x + bboxes.at(i).width, bboxes.at(i).y + bboxes.at(i).height, 1);
		
		cout << "coord1 nach trans " << coord1.at<int>(0, 0) << " _ " << coord1.at<int>(1, 0) << " _ " << coord1.at<int>(2, 0) << endl;
		std::cout << std::endl;
		//neuen 0-Punkt berechnen
		coord2.at<int>(0, 0) = 0;
		coord2.at<int>(1, 0) = 0;
		coord2.at<int>(2, 0) = 1;
		coord2 = trans*coord2;
		//durch z teilen
		coord2.at<int>(0, 0) = coord2.at<int>(0, 0) / coord2.at<int>(2, 0);
		coord2.at<int>(1, 0) = coord2.at<int>(1, 0) / coord2.at<int>(2, 0);
		//0-Punkt addieren
		coord1.at<int>(0, 0) = coord1.at<int>(0, 0) - coord2.at<int>(0, 0);
		coord1.at<int>(1, 0) = coord1.at<int>(1, 0) - coord2.at<int>(1, 0);
		//Maximalwerte einspeichern
		coord3.at<int>(0, 0) = 0 - coordZ.at(0) + 1;
		coord3.at<int>(1, 0) = 0 - coordZ.at(2) + 1;
		coord4.at<int>(0, 0) = coordZ.at(1) - coordZ.at(0) + 1;
		coord4.at<int>(1, 0) = coordZ.at(3) - coordZ.at(2) + 1;

		cout << "Bildpunkte:coord1 " << coord1.at<int>(0, 0) << " _ " << coord1.at<int>(1, 0) << " _ " << coord1.at<int>(2, 0)
			<< "Bildpunkte:coord2 " << coord2.at<int>(0, 0) << " _ " << coord2.at<int>(1, 0) << " _ " << coord2.at<int>(2, 0)
			<< "Bildpunkte:coord3 " << coord3.at<int>(0, 0) << " _ " << coord3.at<int>(1, 0) << " _ " << coord3.at<int>(2, 0)
			<< "Bildpunkte:coord4 " << coord4.at<int>(0, 0) << " _ " << coord4.at<int>(1, 0) << endl;
		std::cout << std::endl;


		cout << "Groeße des Zwischenspeichers anpassen" << endl;
		 img = Mat::zeros(coord4.at<int>(0, 0), coord4.at<int>(1, 0), CV_64F);

		cout << "fuer jeden Punkt im FeatureFeld" << endl;
		std::cout << std::endl;
		for (w = 0; w < coord4.at<int>(0, 0) - coord1.at<int>(0, 0); w++) //x-koordinate vom Ausschnitt
		{
			for (h = 0; h < coord4.at<int>(1, 0) - coord1.at<int>(1, 0); h++)//y-koordinate vom Ausschnitt 
			{
				img.at<int>(w, h) = image.at<int>(w + coord1.at<int>(0, 0), h + coord1.at<int>(1, 0)); //Zwischenspeicher befüllen von 0,0 an
				//cout << "w,h: (" << w << "," << h << ")"  << ends;
			}
		}
		cout << "ImageName: " << name << endl;
		Speicher.Save(img, name, name); //Abspeichern
												  //	img.release(); //Zwischenspeicher leeren
	}



}
