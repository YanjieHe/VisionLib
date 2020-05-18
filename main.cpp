#include <iostream>
#include "BMP.hpp"
#include "Mat.hpp"
using namespace std;

int main(int argc, char** argv)
{
	Byte *pixels;
	uint32_t bytesPerPixel = 0;
	BmpInfo bmpInfo;

	ReadImage("img.bmp", pixels, bmpInfo, bytesPerPixel);
	WriteImage("img2.bmp", pixels, bmpInfo, bytesPerPixel);

	Mat mat(pixels, bmpInfo.width, bmpInfo.height);
	free(pixels);
	cin.get();
	return 0;
}