#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{   
	Mat image = imread("adam1.png", 0);
	Mat imageOut = imread("adam1.png", 0);
	Ptr<cv::MSER> mser = MSER::create();
	vector< vector<Point > > ptblobs;
	vector<Rect> bboxes;
	mser->detectRegions(image, ptblobs, bboxes);

	vector <KeyPoint >keypoints;
	vector <Point2f> speicher;
	for (int i = 0; i < ptblobs.size();i++)
	{
		for (int j = 0; j < ptblobs.at(i).size(); j++) {
			Point pt = ptblobs.at(i).at(j);
			speicher[i] = Point2f(pt.x, pt.y);
		}
	};

	KeyPoint::convert(speicher, keypoints);
	drawKeypoints(image, keypoints, imageOut);
	

	namedWindow("image");
	imshow("image", imageOut);
	waitKey(0);
}
