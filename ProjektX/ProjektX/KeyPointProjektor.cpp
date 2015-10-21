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
	Mat tlt = (Mat_<double>(3, 3) <<
		1, 0, (0 - coordZ.at(0)),
		0, 1, (0 - coordZ.at(2)),
		0, 0, 1);
	string ad = "";
	double xmin; double ymin; double xmax; double ymax;
	Mat img;int i; double w; double h;
	Speicher Speicher;
	Projektion Proj;
	bboxes = boxes;
	//für jedes FeatureFeld
	for (i = 0; i < bboxes.size(); i++)
	{
		ad = "k"+to_string(i);
		
		cout << endl;
		cout << "KeypointNr:"   << i << endl;
		std::cout << std::endl;
		Mat coord1 = (Mat_ <double>(3, 1) << bboxes.at(i).x, bboxes.at(i).y, 1);
		Mat coord2 = (Mat_ <double>(3, 1) << bboxes.at(i).x, bboxes.at(i).y + bboxes.at(i).height, 1);
		Mat coord3 = (Mat_ <double>(3, 1) << bboxes.at(i).x + bboxes.at(i).width, bboxes.at(i).y, 1);
		Mat coord4 = (Mat_ <double>(3, 1) << bboxes.at(i).x + bboxes.at(i).width, bboxes.at(i).y + bboxes.at(i).height, 1);
		
		cout << "coord1 vor trans " << coord1.at<double>(0, 0) << " _ " << coord1.at<double>(1, 0) << " _ " << coord1.at<double>(2, 0) << endl;
		//neuen 0-Punkt berechnen
		coord1 = Proj.PunktVerschieben(coord1, tlt, trans);
		coord2 = Proj.PunktVerschieben(coord2, tlt, trans);
		coord3 = Proj.PunktVerschieben(coord3, tlt, trans);
		coord4 = Proj.PunktVerschieben(coord4, tlt, trans);
		cout << "coord1 nach trans " << coord1.at<double>(0, 0) << " _ " << coord1.at<double>(1, 0) << " _ " << coord1.at<double>(2, 0) << endl;
		//Maximalwerte einspeichern
		/*
		coord3.at<double>(0, 0) = 0 - coordZ.at(0) + 1;
		coord3.at<double>(1, 0) = 0 - coordZ.at(2) + 1;
		coord4.at<double>(0, 0) = coordZ.at(1) - coordZ.at(0) + 1;
		coord4.at<double>(1, 0) = coordZ.at(3) - coordZ.at(2) + 1;
		*/
		double EckpunkteX[4] = { coord1.at<double>(0, 0) , coord2.at<double>(0, 0) , coord3.at<double>(0, 0) , coord4.at<double>(0, 0) };
		double EckpunkteY[4] = { coord1.at<double>(1, 0) , coord2.at<double>(1, 0) , coord3.at<double>(1, 0) , coord4.at<double>(1, 0) };
		xmin = EckpunkteX[0];
		xmax = EckpunkteX[0];
		ymin = EckpunkteY[0];
		ymax = EckpunkteY[0];
		for (int i = 1; i < 4; i++)
		{
			// größtes X finden
			xmax = max(EckpunkteX[i], xmax);
			// größtes Y finden
			ymax = max(EckpunkteY[i], ymax);
			// kleinstes X finden
			xmin = min(EckpunkteX[i], xmin);
			// kleinstes Y finden
			ymin = min(EckpunkteY[i], ymin);
		}
		/*
		cout << "xmin: " << xmin << "ymin: " << ymin << "xamx: " << xmax << "ymax: " << ymax  << endl;
		std::cout << std::endl;
		xmin = xmin - coordZ.at(0);
		ymin = ymin - coordZ.at(1);
		xmax = xmax - coordZ.at(0);
		ymax = ymax - coordZ.at(1);
		*/
		cout << endl;
		cout << "xmin: " << xmin << "ymin: " << ymin << "xamx: " << xmax << "ymax: " << ymax <<"imagesize: "<<image.size()<< endl;		
		img.size() = Size(xmax-xmin,ymax-ymin);
		//cout << "Groeße des Zwischenspeichers anpassen" << endl;
		//if((xmin>=0)&&(xmax-xmin>0)&&(xmin<img.size().width)&&((xmax-xmin)<=img.size().width) && (ymin>=0) && (ymax - ymin>0) && (ymin<img.size().height) && ((ymax - ymin)<=img.size().height))
		img = image(Rect(xmin, ymin, xmax - xmin , ymax - ymin ));
		//else cout << "KOORDINATEN SIND FEHLERHAFT" << endl;
		//cout << "fuer jeden Punkt im FeatureFeld" << endl;
		std::cout << std::endl;

		cout << "ImageName: " << ad<<"|-|"<<name << endl;
		if (img.size().height + img.size().width > 0)
			Speicher.Save(img, ad, ad + name); //Abspeichern
		else
			cout << "BILD IST NICHT BEFÜLLT" << endl;
												  //	img.release(); //Zwischenspeicher leeren
	}



}
