#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <iomanip>
#include <cmath>


using namespace cv;

class Projektion
{
public:
	Projektion();
	~Projektion();
	Mat bildRotieren( Mat image, double alpha, double beta, double gamma);
	Mat matrixErrechnen(Mat image, double alpha, double beta, double gamma);
	Size sizeBerechnen(Mat trans, Mat image);
	Mat bildDrehen(Mat image, Mat trans, Size sze);
};