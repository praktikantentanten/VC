#include "Speicher.h"
#include <windows.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <sddl.h>
#include <stdio.h>
#include <aclapi.h>
#include <tchar.h>

Speicher::Speicher()
{
}


Speicher::~Speicher()
{
}
bool Speicher::Save(cv::Mat img, std::string ordner, std::string uordner)
{

	//Ordner für Eingangsbild
	SetFolder(ordner);
	//Unterordner für proj. Bild
	SetFolder(ordner + "\\" + ordner);

	//Bilder speichern
	std::string buffer = uordner + ".png";
	cv::imwrite(buffer, img);

	return true;
}

/// Bildpfad zwischengespeichert, Unterordner fuer Keypoints erzeugt, Arbeitsumgebung auf erstellten Unterordner gesetzt
bool Speicher::Save(cv::Mat img1, cv::Mat img2, std::string ordner, std::string uordner)
{
	Save(img1, ordner, uordner);
	std::string buffer2 = "keypoints" + uordner + ".png";
	cv::imwrite(buffer2, img2);
	
	return true;
}

//Ordner erzeugen und als Arbeitsumgebung setzen
bool Speicher::SetFolder(std::string ordner)
{
	std::string buf = "C:\\" + ordner;
	LPSTR curDirectory = const_cast<char *> (buf.c_str());

	//Ordner erzeugen
	CreateDirectory(curDirectory, NULL);

	//als Arbeitsumgebung setzen
	SetCurrentDirectory(curDirectory);
	return true;
}



