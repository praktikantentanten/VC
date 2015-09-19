#include "Mathe.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <iostream>



Mathe::Mathe()
{
}


Mathe::~Mathe()
{
}

double Mathe::WinkelZuBogen(double winkel)
{
	return winkel *CV_PI / 180.;
}
double Mathe::WinkelZuGrad(double wert)
{
	return wert / CV_PI * 180.;
}
