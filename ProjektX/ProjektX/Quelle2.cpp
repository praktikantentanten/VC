#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;


// MSER Mit Elipsen - Einzelne_Keypoint-Funktion in den Kommentaren
int main1(int argc, char *argv[])
{   //Bild wird geladen, MSER und Speichervariablen werden erstellt
	Mat image = imread("adam1.png", 0);
	Mat imageOut = imread("adam1.png", 0);
	Ptr<cv::MSER> mser = MSER::create();
	vector< vector<Point > > ptblobs;
	vector<Rect> bboxes;
	//MSER Detect wird ausgeführt 
	mser->detectRegions(image, ptblobs, bboxes);



	for (int i = 0; i < ptblobs.size(); i++)
	{
		RotatedRect rrr = fitEllipse(ptblobs.at(i));
		ellipse(imageOut,rrr, (0,255,255 )) ;
	}
	imwrite("adamElipse.png", imageOut);
	//Bild anzeigen
	namedWindow("image");
	imshow("image", imageOut);
	waitKey(0);
	return -1;
}
///Umrechnung von Point -> Point2f für drawKeypoints
/*vector <KeyPoint >keypoints;
vector <Point2f> speicher;
for (int i = 0; i < ptblobs.size();i++)
{
for (int j = 0; j < ptblobs.at(i).size(); j++)
{
Point pt = ptblobs.at(i).at(j);
speicher.push_back(Point2f(pt.x, pt.y)); //hinzufügen von PointKoordinaten x und y zu Zwischenspeicher
}
};


//Umrechnung von Point2f -> Keypoints
//KeyPoint::convert(speicher, keypoints);
//zeichnen der Keypoints
//drawContours(imageOut)
//drawKeypoints(image, keypoints, imageOut);
*/

/// rotateImage(const Mat &input, Mat &output, double alpha, double beta, double gamma, double dx, double dy, double dz, double f);
/*
void rotateImage(const Mat &input, Mat &output, double alpha=90, double beta=90, double gamma=90, double dx=200, double dy=200, double dz=0, double f=0)
{
	alpha = (alpha - 90.)*CV_PI / 180.;
	beta = (beta - 90.)*CV_PI / 180.;
	gamma = (gamma - 90.)*CV_PI / 180.;

	// get width and height for ease of use in matrices
	double w = (double)input.cols;
	double h = (double)input.rows;

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

	// Apply matrix transformation
	warpPerspective(input, output, trans, input.size(), INTER_LANCZOS4);

}
*/