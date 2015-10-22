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
	double xmin; double ymin; double xmax; double ymax; bool flag;
	Mat img;int i; double w; double h;
	Speicher Speicher;
	Projektion Proj;
	bboxes = boxes;
	Speicher.SetFolder("praktikum");
	Speicher.verzeichnis = "C:\\praktikum\\";
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
		
		//cout << "coord1 vor trans " << coord1.at<double>(0, 0) << " _ " << coord1.at<double>(1, 0) << " _ " << coord1.at<double>(2, 0) << endl;
		//neuen 0-Punkt berechnen
		coord1 = Proj.PunktVerschieben(coord1, trans);
		coord2 = Proj.PunktVerschieben(coord2, trans);
		coord3 = Proj.PunktVerschieben(coord3, trans);
		coord4 = Proj.PunktVerschieben(coord4, trans);
		//cout << "coord1 nach trans " << coord1.at<double>(0, 0) << " _ " << coord1.at<double>(1, 0) << " _ " << coord1.at<double>(2, 0) << endl;
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
		
		cout << "xmin: " << xmin << "ymin: " << ymin << "xamx: " << xmax << "ymax: " << ymax  << endl;
		std::cout << std::endl;
		
		cout << endl;
		cout << "xmin: " << xmin << " ymin: " << ymin << " xamx: " << xmax << " ymax: " << ymax << " xmax-xmin "<< xmax - xmin << " ymax-ymin " << ymax - ymin <<" imagesize: "<<image.size()<< endl;
		img.size() = Size(xmax-xmin,ymax-ymin);
		flag = (xmin >= 0) && (ymin >= 0) && (ymax <= image.size().height) && (xmax <= image.size().width);
		//cout << "Groeße des Zwischenspeichers anpassen" << endl;
		if(flag)
		img = image(Rect(xmin, ymin, xmax - xmin , ymax - ymin ));
		else cout << "KOORDINATEN SIND FEHLERHAFT" << endl;
		std::cout << std::endl;

		cout << "ImageName: " << ad<<"|-|"<<name << endl;
		if (flag)
			Speicher.Save(img, ad, ad + name); //Abspeichern
		else
			cout << "BILD IST NICHT BEFÜLLT" << endl;
												  //	img.release(); //Zwischenspeicher leeren
	}



}
