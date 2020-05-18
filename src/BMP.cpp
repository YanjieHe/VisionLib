#include "BMP.hpp"
using std::cout;
using std::endl;
using std::ios;

void ReadImage(string fileName, Byte *& pixels, BmpInfo & bmpInfo, uint32_t & bytesPerPixel)
{
	ifstream imageFile(fileName, ios::in | ios::binary);
	if (imageFile)
	{
		imageFile.read((char*)&bmpInfo.bmpSignature, 2);
		imageFile.read((char*)&bmpInfo.fileSize, sizeof(uint32_t));
		imageFile.read((char*)&bmpInfo.reserved, sizeof(uint32_t));
		imageFile.read((char*)&bmpInfo.dataOffset, sizeof(uint32_t));

		imageFile.read((char*)&bmpInfo.sizeOfTheHeader, sizeof(uint32_t));
		imageFile.read((char*)&bmpInfo.width, sizeof(uint32_t));
		imageFile.read((char*)&bmpInfo.height, sizeof(uint32_t));

		imageFile.read((char*)&bmpInfo.planes, sizeof(uint16_t));
		imageFile.read((char*)&bmpInfo.bitsPerPixel, sizeof(uint16_t));

		imageFile.read((char*)&bmpInfo.compression, sizeof(uint32_t));
		imageFile.read((char*)&bmpInfo.imageSize, sizeof(uint32_t));
		imageFile.read((char*)&bmpInfo.resolutionX, sizeof(uint32_t));
		imageFile.read((char*)&bmpInfo.resolutionY, sizeof(uint32_t));
		imageFile.read((char*)&bmpInfo.colorsUsed, sizeof(uint32_t));
		imageFile.read((char*)&bmpInfo.importantColors, sizeof(uint32_t));

		if (bmpInfo.bitsPerPixel)
		{
			cerr << "Bits per pixel < 8" << endl;
			exit(-1);
		}
		uint32_t width = bmpInfo.width;
		uint32_t height = bmpInfo.height;
		uint16_t bitsPerPixel = bmpInfo.bitsPerPixel;

		std::cout << "file size: " << bmpInfo.fileSize << endl;
		std::cout << "reserved: " << bmpInfo.reserved << endl;
		std::cout << "data offset: " << bmpInfo.dataOffset << endl;

		cout << "size of the header: " << bmpInfo.sizeOfTheHeader << endl;
		cout << "width: " << bmpInfo.width << endl;
		cout << "height: " << bmpInfo.height << endl;
		cout << "planes: " << bmpInfo.planes << endl;
		cout << "bits per pixel: " << bmpInfo.bitsPerPixel << endl;
		cout << "compression: " << bmpInfo.compression << endl;
		std::cout << "image size: " << bmpInfo.imageSize << endl;
		cout << "resolution X: " << bmpInfo.resolutionX << endl;
		cout << "resolution Y: " << bmpInfo.resolutionY << endl;
		cout << "colors used: " << bmpInfo.colorsUsed << endl;
		cout << "important colors: " << bmpInfo.importantColors << endl;


		bytesPerPixel = (static_cast<int32_t>(bitsPerPixel)) / 8;

		int paddedRowSize = (int)(4 * ceil((float)(width) / 4.0f)) * bytesPerPixel;
		int unpaddedRowSize = width * bytesPerPixel;
		int totalSize = unpaddedRowSize * height;
		pixels = (Byte*)malloc(totalSize);
		Byte *currentRowPointer = pixels + (height - 1) * unpaddedRowSize;
		for (uint32_t i = 0; i < height; i++)
		{
			imageFile.seekg(bmpInfo.dataOffset + (i*paddedRowSize));
			imageFile.read((char*)currentRowPointer, unpaddedRowSize);
			currentRowPointer -= unpaddedRowSize;
		}
		imageFile.close();
	}
	else
	{
		std::cerr << "file not found" << endl;
		std::cin.get();
		exit(-1);
	}
}

void WriteImage(string fileName, Byte * pixels, BmpInfo & bmpInfo, uint32_t & bytesPerPixel)
{
	if (bmpInfo.bitsPerPixel)
	{
		cerr << "Bits per pixel < 8" << endl;
		exit(-1);
	}
	ofstream outputFile(fileName, ios::out | ios::binary);

	outputFile.write((char*)&bmpInfo.bmpSignature, 2);
	outputFile.write((char*)&bmpInfo.fileSize, sizeof(uint32_t));
	outputFile.write((char*)&bmpInfo.reserved, sizeof(uint32_t));
	outputFile.write((char*)&bmpInfo.dataOffset, sizeof(uint32_t));

	outputFile.write((char*)&bmpInfo.sizeOfTheHeader, sizeof(uint32_t));
	outputFile.write((char*)&bmpInfo.width, sizeof(uint32_t));
	outputFile.write((char*)&bmpInfo.height, sizeof(uint32_t));

	outputFile.write((char*)&bmpInfo.planes, sizeof(uint16_t));
	outputFile.write((char*)&bmpInfo.bitsPerPixel, sizeof(uint16_t));

	outputFile.write((char*)&bmpInfo.compression, sizeof(uint32_t));
	outputFile.write((char*)&bmpInfo.imageSize, sizeof(uint32_t));
	outputFile.write((char*)&bmpInfo.resolutionX, sizeof(uint32_t));
	outputFile.write((char*)&bmpInfo.resolutionY, sizeof(uint32_t));
	outputFile.write((char*)&bmpInfo.colorsUsed, sizeof(uint32_t));
	outputFile.write((char*)&bmpInfo.importantColors, sizeof(uint32_t));

	uint32_t width = bmpInfo.width;
	uint32_t height = bmpInfo.height;
	int32_t paddedRowSize = (int)(4 * ceil((float)width / 4.0f)) * bytesPerPixel;
	int unpaddedRowSize = width * bytesPerPixel;
	for (uint32_t i = 0; i < height; i++)
	{
		int pixelOffset = ((height - i) - 1) * unpaddedRowSize;
		outputFile.write((char*)&pixels[pixelOffset], paddedRowSize);
	}
	outputFile.close();
}
