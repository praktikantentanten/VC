#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "Mathe.h"


using namespace cv;

class Projektion
{
public:
	
	Projektion();
	~Projektion();
	Mat bildRotieren(Mat image, double alpha, double beta, double gamma);
	Mat bildRotieren(Mat image, double theta, double phi);
	Mat matrixErrechnen(double alpha, double beta, double gamma);
	Size Projektion::sizeBerechnen(Mat oL, Mat uL, Mat oR, Mat uR,Mat transL);
	//BildInput
	Mat image;
	//BildOutput
	Mat imageOut;
	//Transformationsmatrix
	Mat trans;

private:	
	//Objekt für mathem. Berechnungen
	Mathe M; 
	//Größe des BildInputs
	Size size; 
	//Größe des BildOutputs
	Size sizeOut;
	double  xmin, xmax, ymin, ymax ; // Minimale und maximale X und Y Werte der Eckpunkte des Bildes

};