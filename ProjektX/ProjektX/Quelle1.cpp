#include <opencv2/highgui/highgui.hpp>
#include <opencv2\features2d\features2d.hpp>
#include <opencv2\features2d.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	std::cout << "OpenCV version: "
		<< CV_MAJOR_VERSION << "."
		<< CV_MINOR_VERSION << "."
		<< CV_SUBMINOR_VERSION
		<< std::endl;
	Mat im = imread("adam1.png", 0);
	if (im.empty())
	{
		cout << "Cannot open image!" << endl;
		return -1;
	}
	Mat gray;
	cvtColor(im, gray, cv::COLOR_BGR2GRAY);
	int mnArea = 40 * 40;
	int mxArea = im.rows*im.cols*0.4;
	vector< vector< Point > > ptblobs;
	vector<Rect> bboxes;
	chrono::time_point<chrono::system_clock> start, end;

	start = chrono::system_clock::now();

	Ptr<cv::MSER> mser = cv::MSER::create(1, mnArea, mxArea, 0.25, 0.2);
	mser->detectRegions(gray, ptblobs, bboxes);
	
	MserFeatureDetector mser(1, mnArea, mxArea, 0.25, 0.2);
	mser(gray, ptblobs); 

	
	end = std::chrono::system_clock::now();

	chrono::duration<double> elapsed_seconds = end - start;
	time_t end_time = chrono::system_clock::to_time_t(end);

	cout << "finished computation at " << ctime(&end_time)
		<< "elapsed time: " << elapsed_seconds.count() << "s\n";

	namedWindow("image", cv::WINDOW_NORMAL);
	imshow("image", im);
	waitKey(0);

	return 0;
}