#pragma once
//#include <windows.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>

class Speicher
{
public:
	Speicher();
	~Speicher();
	bool Speicher::Save(cv::Mat img1, cv::Mat img2, std::string ordner, std::string uordner);
	bool SetFolder(std::string ordner);
	DWORD AddAceToObjectsSecurityDescriptor(
		LPTSTR pszObjName,          // name of object
		SE_OBJECT_TYPE ObjectType,  // type of object
		LPTSTR pszTrustee,          // trustee for new ACE
		TRUSTEE_FORM TrusteeForm,   // format of trustee structure
		DWORD dwAccessRights,       // access mask for new ACE
		ACCESS_MODE AccessMode = GRANT_ACCES,     // type of ACE
		DWORD dwInheritance         // inheritance flags for new ACE
		)
	//LPSTR curDirectory;
};

