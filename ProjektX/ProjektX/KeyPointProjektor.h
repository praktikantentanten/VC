#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class KeyPointProjektor
{
public:
	KeyPointProjektor();
	~KeyPointProjektor();
	Mat keyPointsProj(Mat keyPoints, double keyPointLength, Mat trans);
	Mat keypoints;
	Mat transMatrix;
};

