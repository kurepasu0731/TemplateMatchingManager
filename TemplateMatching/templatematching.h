#pragma once

#include <opencv2/opencv.hpp>

#define DLLExport __declspec (dllexport)


using namespace cv;


extern "C" {
	DLLExport void templateMatching(unsigned char* const data, int width, int height, int templatenumber, double thresh, int& x, int& y);

	DLLExport void openWindow(const char* windowName);

	DLLExport void closeWindow(const char* windowName);

}