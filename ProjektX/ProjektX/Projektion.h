#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace cv;

class Projektion
{
public:
	Projektion();
	~Projektion();


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
	Mat change(Mat image,double rand =0.5, double alpha = 90, double beta = 90, double gamma = 90, double dx = 90, double dy = 90, double dz = 90)
	{
			
			double f = dz;
			Mat imageOut = image;

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

			
			Size x = Size((double)image.size().height*(rand+1), (double)image.size().width*(rand + 1));
			///Size x = Size((double)image.size().height, (double)image.size().width);

			// Apply matrix transformation
			warpPerspective(image, imageOut, trans, x, INTER_LANCZOS4);
			return imageOut;
		
	};
	
};

