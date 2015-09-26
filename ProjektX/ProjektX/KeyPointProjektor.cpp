#include "KeyPointProjektor.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


KeyPointProjektor::KeyPointProjektor()
{
}


KeyPointProjektor::~KeyPointProjektor()
{
}
Mat KeyPointProjektor::keyPointsProj(Mat keyPoints, double keyPointLength, Mat trans)
{
	//Globale Variablen mit Eingaben füllen
	keypoints = keyPoints;
	transMatrix = trans;
	//projezierte Keypoints berechnen 
	// Keypoints an der Position, an der sie sind oder einfach hintereinander gereiht ? Verarbeitung durch warpPerspective oder einzelnd ?
	int i;
	int j;
	while (i < keypoints.cols && j < keypoints.rows) {
		//keypoints.at<double>(i, j) = keyPoints.at<double>(i, j) *transMatrix;
	
	}
	//projezierte Keypoints speichern

	//projezierte Keypoints ausgeben
	return keypoints;

}
