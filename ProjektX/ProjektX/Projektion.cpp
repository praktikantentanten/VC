#include "Projektion.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include "Mathe.h"
#include <iostream>

using namespace cv;

Projektion::Projektion()
{	
}

Projektion::~Projektion()
{
}

/*
input: the image that you want rotated.
output: the Mat object to put the resulting file in.
alpha: the rotation around the x axis
beta: the rotation around the y axis
gamma: the rotation around the z axis (basically a 2D rotation)
*/

Mat Projektion::bildRotieren(Mat img, double alpha, double beta, double gamma )
{
	//Setzen der globalen Variablen
	image = img;
	size = image.size();
	sizeOut = size;

	//Hilfsfunktionen für Berechnung der Matrix und der Bildgröße
	trans = matrixErrechnen(alpha, beta, gamma);
	
	//Anwenden von warpPerspective mit errechneter Matrix
	warpPerspective(image, imageOut, trans, sizeOut, INTER_LANCZOS4);
	//Bild ausgeben
	return imageOut;

};

/*
überladene bildRotieren für Kugelkoordinaten
*/
Mat Projektion::bildRotieren(Mat image, double theta, double phi)
{
	//Umrechnung der Koordinaten
	return bildRotieren(image, theta*cos(M.WinkelZuBogen(phi)) + 90, theta*sin(M.WinkelZuBogen(phi)) + 90, 90);

}

/*
input: the image properties that you want rotated.
output: the Mat object to put the resulting file in. (global 'sizeOut' changed)
alpha: the rotation around the x axis 
beta: the rotation around the y axis
gamma: the rotation around the z axis (Drehung des ganzen Bildes)
*/
Mat Projektion::matrixErrechnen(double alpha = 90, double beta = 90, double gamma = 90)
{
	// get width and height for ease of use in matrices
	double w = (double)size.width;
	double h = (double)size.height;

	// Translationsvariablen errechnen
	double dx = 0; double dy = 0; // werden später errechnet
	double dz = sqrt(w*w + h*h); //Bilddiagonale
	double f = dz; // Entfernung zum Bild == Distanz von Kamera zu Bild
	


	// Winkelumrechnung 
	alpha = M.WinkelZuBogen(alpha - 90);
	beta = M.WinkelZuBogen(beta-90);
	gamma = M.WinkelZuBogen(gamma - 90);
	
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
	
	//Zwischenschritt: Größe des Bildes berechnen ---------------------------
	sizeOut = sizeBerechnen();
	//-----------------------------------------------------------------------

	//Translationmatrix (Zurechtrücken des Bildes)
	Mat tlt = (Mat_<double>(3, 3) <<
		1, 0, (0 - xmin),
		0, 1, (0 - ymin),
		0, 0, 1);

	return tlt*trans;

};

/*
Berechnung der Größe des neuen Bildes 
*/
Size Projektion::sizeBerechnen() {
	//Obenlinks
	Mat oL = (Mat_<double>(3, 1) << 0, 0, 1);
	//UntenLinks
	Mat uL = (Mat_<double>(3, 1) << 0, size.height - 1, 1);
	//ObenRechts
	Mat oR = (Mat_<double>(3, 1) << size.width - 1, 0, 1);
	//UntenRechts
	Mat uR = (Mat_<double>(3, 1) << size.width - 1, size.height - 1, 1);

	// Verschiebung der Eckpunkte durch Matrix berechnen.
	oL = trans*oL;
	uL = trans*uL;
	oR = trans*oR;
	uR = trans*uR;
	

	//Eckpunkte, aufgeteilt in Koordinatenachsen, durch z-Wert geteilt und gespeichert
	double EckpunkteX[4] = { oL.at<double>(0, 0) / oL.at<double>(2, 0), oR.at<double>(0, 0) / oR.at<double>(2, 0), uL.at<double>(0, 0) / uL.at<double>(2, 0), uR.at<double>(0, 0) / uR.at<double>(2, 0) };
	double EckpunkteY[4] = { oL.at<double>(1, 0) / oL.at<double>(2, 0), oR.at<double>(1, 0) / oR.at<double>(2, 0), uL.at<double>(1, 0) / uL.at<double>(2, 0), uR.at<double>(1, 0) / uR.at<double>(2, 0) };


	// größtes X finden
	for (int i = 0; i < 4; i++)
		xmax = max(EckpunkteX[i], xmax);

	// größtes Y finden
	for (int i = 0; i < 4; i++)
		ymax = max(EckpunkteY[i], ymax);
	xmin = xmax;
	// kleinstes X finden
	for (int i = 0; i < 4; i++)
		xmin = min(EckpunkteX[i], xmin);
	// kleinstes Y finden
	ymin = ymax;
	for (int i = 0; i < 4; i++)
		ymin = min(EckpunkteY[i], ymin);



	//Ausgabe der einzelnen X,Y,Z-Werte zur Kontrolle

	std::cout << "z:" << oL.at<double>(2, 0) << " " << oR.at<double>(2, 0) << " " << uL.at<double>(2, 0) << " " << uR.at<double>(2, 0) << " " << std::endl;
	std::cout << std::endl;
	std::cout << EckpunkteX[0] << " " << EckpunkteX[1] << " " << EckpunkteX[2] << " " << EckpunkteX[3] << " xmax:" << xmax << " xmin:" << xmin << std::endl;
	std::cout << EckpunkteY[0] << " " << EckpunkteY[1] << " " << EckpunkteY[2] << " " << EckpunkteY[3] << " ymax:" << ymax << " ymin:" << ymin << std::endl;
	

	//Errechnen der Bildgröße des zu erzeugenden Bilds
	sizeOut = Size((xmax - xmin + 1), ymax - ymin + 1);
};


