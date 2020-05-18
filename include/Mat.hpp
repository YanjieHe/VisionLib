#ifndef MAT_HPP
#define MAT_HPP
#include <cstdint>
#include <memory>
#include <vector>

using Byte = uint8_t;

struct BgrColor
{
	Byte blue;
	Byte green;
	Byte red;
};

class Mat
{
public:
	int width;
	int height;
	std::shared_ptr<std::vector<BgrColor>> data;

	Mat(Byte* pixels, int width, int height)
	{
		data = std::make_shared<vector<BgrColor>>(width * height);
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				data->at(i * width + j).blue = pixels[i * width * 3 + j * 3];
				data->at(i* width + j).green = pixels[i * width * 3 + j * 3 + 1];
				data->at(i * width + j).red = pixels[i * width * 3 + j * 3 + 2];
			}
		}
	}
};

#endif // MAT_HPP