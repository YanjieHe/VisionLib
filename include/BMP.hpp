#ifndef BMP_HPP
#define BMP_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

using std::string;
using std::ifstream;
using std::ofstream;
using Byte = int8_t;

struct BmpInfo
{
	// Bitmap File Header
	char bmpSignature[2];
	uint32_t fileSize;
	uint32_t reserved;
	uint32_t dataOffset;

	// Bitmap Information Header
	uint32_t sizeOfTheHeader;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint16_t bitsPerPixel;
	uint32_t compression;
	uint32_t imageSize;
	uint32_t resolutionX;
	uint32_t resolutionY;
	uint32_t colorsUsed;
	uint32_t importantColors;
};

void ReadImage(string fileName, Byte *&pixels, BmpInfo& bmpInfo, uint32_t& bytesPerPixel);

void WriteImage(string fileName, Byte *pixels, BmpInfo& bmpInfo, uint32_t& bytesPerPixel);

#endif // BMP_HPP