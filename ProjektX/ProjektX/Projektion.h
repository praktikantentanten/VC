#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cmath>


using namespace cv;

class Projektion
{
public:
	Projektion();
	~Projektion();
	template <typename T> int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}

	/*
	input: the image that you want rotated.
	output: the Mat object to put the resulting file in.
	alpha: the rotation around the x axis
	beta: the rotation around the y axis
	gamma: the rotation around the z axis (basically a 2D rotation)
	dx: translation along the x axis
	dy: translation along the y axis
	dz: translation along the z axis (distance to the image)
	f: focal distance (distance between camera and image, a smaller number exaggerates the effect)
	*/
	Mat change(Mat image, double alpha = 90, double beta = 90, double gamma = 90, double dx = 300, double dy = 300)
	{

			//dy = -(alpha-90)/30*(double)image.cols/2;
		    //dx = -(alpha-90)/30*(double)image.rows/2;
			double dz = 300;//sqrt((double)image.cols*(double)image.cols+ (double)image.rows*(double)image.rows);
			double f = dz;
			Mat imageOut = image;


			// Winkelberechnung 
			alpha = (alpha - 90.)*CV_PI / 180.;
			beta = (beta - 90.)*CV_PI / 180.;
			gamma = (gamma - 90.)*CV_PI / 180.;
			
			// get width and height for ease of use in matrices
			double w = (double)image.cols;
			double h = (double)image.rows;

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

			//Obenlinks
			Mat OL = (Mat_<double>(1, 3) << 0, 0,  0);
			//ObenRechts
			Mat OR = (Mat_<double>(1, 3) << image.size().width, 0, 0);
			//UntenLinks
			Mat UL = (Mat_<double>(1, 3) << 0, image.size().height, 0);
			//UntenRechts
			Mat UR = (Mat_<double>(1, 3) << image.size().width, image.size().height, 0);

			Mat OLtrans = OL*trans;
			Mat ULtrans = UL*trans;
			Mat ORtrans = OR*trans;
			Mat URtrans = UR*trans;
		cv:InputArray EckpunkteX = (OL.at<double>(0, 0), OR.at<double>(0, 0), UL.at<double>(0, 0), UR.at<double>(0, 0));
			double Eckpunktey[] = {	OL.at<double>(0, 1), OR.at<double>(0, 1),UL.at<double>(0, 1), UR.at<double>(0, 1)};
			
			double x;
			double y; 
		//	minMaxLoc( EckpunkteX, x);
			




			Size sze = Size(w*1.5,h*1.5);
			

			// Apply matrix transformation
			warpPerspective(image, imageOut, trans, sze, INTER_LANCZOS4);
			return imageOut;
		
	};
	
};
/*

if (alpha != 0)
{
	h = h + h *(sgn(alpha)*alpha / 10);
	w = w - w *(sgn(alpha)*alpha / 10);
}
else if (beta != 0)
{
	h = h - h *(sgn(beta)*beta / 10);
	w = w + w *(sgn(beta)*beta / 10);
}
else if (gamma != 0)
{
	h = h + h*(sgn(gamma)*gamma / 10);
	w = w + w*(sgn(gamma)*gamma / 10);
};*/