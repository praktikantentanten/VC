#include "KeyPointDetektor.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;


KeyPointDetektor::KeyPointDetektor()
{
}


KeyPointDetektor::~KeyPointDetektor()
{
}
//MSER

std::vector<cv::Rect>  KeyPointDetektor::Mser(cv::Mat image)
{
	cv::Ptr<cv::MSER> mser = cv::MSER::create();
	vector< vector<cv::Point > > ptblobs;
	vector<cv::Rect> bboxes;
	//MSER Detect wird ausgef�hrt 
	mser->detectRegions(image, ptblobs, bboxes);
	return bboxes; 
}

//SIFT