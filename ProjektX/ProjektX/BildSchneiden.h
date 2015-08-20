#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

class BildSchneiden
{
public:
	BildSchneiden();
	~BildSchneiden();

	///http://www.shervinemami.info/imageTransforms.html


	// Returns a new image that is a cropped version (rectangular cut-out)
	// of the original image.
	IplImage* BildSchneiden::cropImage(const IplImage *img, const CvRect region)
	{
		IplImage *imageCropped;
		CvSize size;

		if (img->width <= 0 || img->height <= 0	|| region.width <= 0 || region.height <= 0) {
			//cerr << "ERROR in cropImage(): invalid dimensions." << endl;
			exit(1);
		}

		if (img->depth != IPL_DEPTH_8U) {
			//cerr << "ERROR in cropImage(): image depth is not 8." << endl;
			exit(1);
		}

		// Set the desired region of interest.
		cvSetImageROI((IplImage*)img, region);
		// Copy region of interest into a new iplImage and return it.
		size.width = region.width;
		size.height = region.height;
		imageCropped = cvCreateImage(size, IPL_DEPTH_8U, img->nChannels);
		cvCopy(img, imageCropped);	// Copy just the region.

		return imageCropped;
	}

};

