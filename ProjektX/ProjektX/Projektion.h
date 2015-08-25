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
	Mat change(Mat image, double alpha = 90, double beta = 90, double gamma = 90, double dx = 0, double dy = 0)
	{

			//dy = -(alpha-90)/30*(double)image.cols/2;
		    //dx = -(alpha-90)/30*(double)image.rows/2;
			double dz = sqrt((double)image.cols*(double)image.cols+ (double)image.rows*(double)image.rows);
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
			Mat OL = (Mat_<double>(3, 1) << 0, 0,  1);
			//ObenRechts
			Mat OR = (Mat_<double>(3, 1) << image.size().width-1, 0, 1);
			//UntenLinks
			Mat UL = (Mat_<double>(3, 1) << 0, image.size().height-1, 1);
			//UntenRechts
			Mat UR = (Mat_<double>(3, 1) << image.size().width-1, image.size().height-1, 1);

			OL = trans*OL;
			UL = trans*UL;
			OR = trans*OR;
			UR = trans*UR;
			double EckpunkteX[4] = { OL.at<double>(0, 0)/ OL.at<double>(2, 0), OR.at<double>(0, 0)/ OR.at<double>(2, 0), UL.at<double>(0, 0)/ UL.at<double>(2, 0), UR.at<double>(0, 0)/UR.at<double>(2, 0) };
			double EckpunkteY[4] = { OL.at<double>(1, 0) / OL.at<double>(2, 0), OR.at<double>(1, 0) / OR.at<double>(2, 0), UL.at<double>(1, 0) / UL.at<double>(2, 0), UR.at<double>(1, 0) / UR.at<double>(2, 0) };
			std::cout <<"z:"<< OL.at<double>(2, 0) << " " << OR.at<double>(2, 0) << " " << UL.at<double>(2, 0) << " " << UR.at<double>(2, 0) << " " << std::endl;
			
			double x;
			double h1;
			double h2;
			double y; 
			double xmin;
			double ymin;
			// größtes X finden
			if (EckpunkteX[0] > EckpunkteX[1])
					h1 = EckpunkteX[0];
			else	h1 = EckpunkteX[1];

			if (EckpunkteX[2] > EckpunkteX[3])
					h2 = EckpunkteX[2];
			else	h2 = EckpunkteX[3];
			if (h1 > h2)
					x = h1;
			else	x = h2;
			
			// größtes Y finden
			if (EckpunkteY[0] > EckpunkteY[1])
					h1 = EckpunkteY[0];
			else	h1 = EckpunkteY[1];

			if (EckpunkteY[2] > EckpunkteY[3])
					h2 = EckpunkteY[2];
			else	h2 = EckpunkteY[3];
			if (h1 > h2)
					y = h1;
			else	y = h2;
			;
			
			// kleinstes X finden
			if (EckpunkteX[0] < EckpunkteX[1])
				h1 = EckpunkteX[0];
			else	h1 = EckpunkteX[1];

			if (EckpunkteX[2] < EckpunkteX[3])
				h2 = EckpunkteX[2];
			else	h2 = EckpunkteX[3];
			if (h1 < h2)
				xmin = h1;
			else	xmin = h2;

			// kleinstes Y finden
			if (EckpunkteY[0] < EckpunkteY[1])
				h1 = EckpunkteY[0];
			else	h1 = EckpunkteY[1];

			if (EckpunkteY[2] < EckpunkteY[3])
				h2 = EckpunkteY[2];
			else	h2 = EckpunkteY[3];
			if (h1 < h2)
				ymin = h1;
			else	ymin = h2;
			;

			std::cout << std::setfill('|');
			std::cout << std::internal << std::showpos;
			std::cout << EckpunkteX[0] <<" "<< EckpunkteX[1]<<" " << EckpunkteX[2] <<" " << EckpunkteX[3] <<" "<<x <<std::endl;
			std::cout << EckpunkteY[0] << " " << EckpunkteY[1] << " " << EckpunkteY[2] << " " << EckpunkteY[3] << " " << y <<std::endl;

			Size sze = Size((x-xmin+1),y-ymin+1 );
			

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