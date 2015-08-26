#include "Projektion.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;

Projektion::Projektion()
{	
}


Projektion::~Projektion()
{
}
template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

/*
input: the image that you want rotated.
output: the Mat object to put the resulting file in.
alpha: the rotation around the x axis
beta: the rotation around the y axis
gamma: the rotation around the z axis (basically a 2D rotation)
*/
Mat Projektion::bildRotieren(Mat image, double alpha = 90, double beta = 90, double gamma = 90)
{
	//Hilfsfunktionen für Berechnung der Matrix und der Bildgröße
	Mat trans = matrixErrechnen(image, alpha, beta, gamma);
	Size sze=sizeBerechnen(trans,image);

	bildDrehen( image,  trans,  sze);

};
/*
input: the image that you want rotated.
output: the Mat object to put the resulting file in.
alpha: the rotation around the x axis 
beta: the rotation around the y axis
gamma: the rotation around the z axis (Drehung)
*/
Mat Projektion::matrixErrechnen(Mat image, double alpha = 90, double beta = 90, double gamma = 90)
{
	// Translationsvariablen errechnen
	double dx = 0, double dy = 0;
	double dz = sqrt((double)image.cols*(double)image.cols + (double)image.rows*(double)image.rows); //Bilddiagonale
	double f = dz; // Entfernung zum Bild == Distanz von Kamera zu Bild
	


	// Winkelberechnung 
	alpha = (alpha - 90.)*CV_PI / 180.;
	beta = (beta - 90.)*CV_PI / 180.;
	gamma = (gamma - 90.)*CV_PI / 180.;

	// get width and height for ease of use in matrices
	double w = (double)image.cols;
	double h = (double)image.rows;

	// Projection 2D -> 3D matrix
	Mat A1 = (Mat_<double>(4, 3) <<
		1, 0, -w / 2,
		0, 1, -h / 2,
		0, 0, 0,
		0, 0, 1);

	// Rotation matrices around the X, Y, and Z axis
	Mat RX = (Mat_<double>(4, 4) <<
		1, 0, 0, 0,
		0, cos(alpha), -sin(alpha), 0,
		0, sin(alpha), cos(alpha), 0,
		0, 0, 0, 1);

	Mat RY = (Mat_<double>(4, 4) <<
		cos(beta), 0, -sin(beta), 0,
		0, 1, 0, 0,
		sin(beta), 0, cos(beta), 0,
		0, 0, 0, 1);

	Mat RZ = (Mat_<double>(4, 4) <<
		cos(gamma), -sin(gamma), 0, 0,
		sin(gamma), cos(gamma), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	// Composed rotation matrix with (RX, RY, RZ)
	Mat R = RX * RY * RZ;

	// Translation matrix
	Mat T = (Mat_<double>(4, 4) <<
		1, 0, 0, dx,
		0, 1, 0, dy,
		0, 0, 1, dz,
		0, 0, 0, 1);

	// 3D -> 2D matrix
	Mat A2 = (Mat_<double>(3, 4) <<
		f, 0, w / 2, 0,
		0, f, h / 2, 0,
		0, 0, 1, 0);

	// Final transformation matrix
	Mat trans = A2 * (T * (R * A1));
};

//Berechnung der Größe des neuen Bildes
Size Projektion::sizeBerechnen(Mat trans, Mat image) {
	//Obenlinks
	Mat oL = (Mat_<double>(3, 1) << 0, 0, 1);
	//UntenLinks
	Mat uL = (Mat_<double>(3, 1) << 0, image.size().height - 1, 1);
	//ObenRechts
	Mat oR = (Mat_<double>(3, 1) << image.size().width - 1, 0, 1);
	//UntenRechts
	Mat uR = (Mat_<double>(3, 1) << image.size().width - 1, image.size().height - 1, 1);

	// Verschiebung der Eckpunkte durch Matrix berechnen.
	oL = trans*oL;
	uL = trans*uL;
	oR = trans*oR;
	uR = trans*uR;
	//Eckpunkte, aufgeteilt in Koordinatenachsen, durch z-Wert geteilt und gespeichert
	double EckpunkteX[4] = { oL.at<double>(0, 0) / oL.at<double>(2, 0), oR.at<double>(0, 0) / oR.at<double>(2, 0), uL.at<double>(0, 0) / uL.at<double>(2, 0), uR.at<double>(0, 0) / uR.at<double>(2, 0) };
	double EckpunkteY[4] = { oL.at<double>(1, 0) / oL.at<double>(2, 0), oR.at<double>(1, 0) / oR.at<double>(2, 0), uL.at<double>(1, 0) / uL.at<double>(2, 0), uR.at<double>(1, 0) / uR.at<double>(2, 0) };
	std::cout << "z:" << oL.at<double>(2, 0) << " " << oR.at<double>(2, 0) << " " << uL.at<double>(2, 0) << " " << uR.at<double>(2, 0) << " " << std::endl;
	
	double xmax, double ymax, double xmin, double ymin;

	// größtes X finden
	for (int i = 0; i < 4; i++)
		xmax = max(EckpunkteX[i], xmax);

	// größtes Y finden
	for (int i = 0; i < 4; i++)
		ymax = max(EckpunkteX[i], ymax);

	// kleinstes X finden
	for (int i = 0; i < 4; i++)
		xmin = max(EckpunkteX[i], xmin);
	// kleinstes Y finden
	for (int i = 0; i < 4; i++)
		ymin = max(EckpunkteX[i], ymin);



	//Ausgabe der einzelnen X,Y-Werte zur Kontrolle
	std::cout << std::setfill('|');
	std::cout << std::internal << std::showpos;
	std::cout << EckpunkteX[0] << " " << EckpunkteX[1] << " " << EckpunkteX[2] << " " << EckpunkteX[3] << " " << xmax << std::endl;
	std::cout << EckpunkteY[0] << " " << EckpunkteY[1] << " " << EckpunkteY[2] << " " << EckpunkteY[3] << " " << ymax << std::endl;

	//Errechnen der Bildgröße des zu erzeugenden Bilds
	Size sze = Size((xmax - xmin + 1), ymax - ymin + 1);

	return sze;
};
		

//Anwenden von warpPerspective mit errechneter Matrix
Mat Projektion::bildDrehen(Mat image,Mat trans,Size sze)
{
	Mat imageOut = image;
	// Apply matrix transformation
	warpPerspective(image, imageOut, trans, sze, INTER_LANCZOS4);
	return imageOut;
	
};

