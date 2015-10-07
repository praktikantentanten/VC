#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

class KeyPointDetektor
{
public:
	KeyPointDetektor();
	~KeyPointDetektor();
	std::vector <cv::Rect> KeyPointDetektor::Mser(cv::Mat image);
};

