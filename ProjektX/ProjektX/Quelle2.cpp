#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{   //Bild wird geladen, MSER und Speichervariablen werden erstellt
	Mat image = imread("adam1.png", 0);
	Mat imageOut = imread("adam2.png", 0);
	Ptr<cv::MSER> mser = MSER::create();
	vector< vector<Point > > ptblobs;
	vector<Rect> bboxes;
	//MSER Detect wird ausgef�hrt 
	mser->detectRegions(image, ptblobs, bboxes);

	warpPerspective( );

	for (int i = 0; i < ptblobs.size(); i++)
	{
		RotatedRect rrr = fitEllipse(ptblobs.at(i));
		ellipse(imageOut,rrr, (0,255,255 )) ;
	}

	imwrite("adam2.png", imageOut);
	//Bild anzeigen
	namedWindow("image");
	imshow("image", imageOut);
	waitKey(0);
}
///Umrechnung von Point -> Point2f f�r drawKeypoints
/*vector <KeyPoint >keypoints;
vector <Point2f> speicher;
for (int i = 0; i < ptblobs.size();i++)
{
for (int j = 0; j < ptblobs.at(i).size(); j++)
{
Point pt = ptblobs.at(i).at(j);
speicher.push_back(Point2f(pt.x, pt.y)); //hinzuf�gen von PointKoordinaten x und y zu Zwischenspeicher
}
};


//Umrechnung von Point2f -> Keypoints
//KeyPoint::convert(speicher, keypoints);
//zeichnen der Keypoints
//drawContours(imageOut)
//drawKeypoints(image, keypoints, imageOut);
*/