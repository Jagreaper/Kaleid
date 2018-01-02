#include "ImageDecoder.hpp"
#include "ImageLoader.hpp"
#include "Kaleid.Imaging\Image.hpp"
#include "STB\stb_image.h"

using namespace Kaleid::IO;
using namespace Kaleid::Imaging;

bool ImagePathDecoder::TryDecode(const char* source, Image* output, void* arg)
{
	int width, height, comp;
	unsigned char* data = LoadImageFromFile(source, &width, &height, &comp, STBI_rgb_alpha);
	int data_length = width * height * comp;

	output->SetSize(width, height);
	output->SetData(data, data_length);

	if (comp == 1)
	{
		ChannelInfo info[1];
		info[0].Type = ChannelType::Gray;
		output->SetChannels(info, comp);
	}
	else if (comp == 2)
	{
		ChannelInfo info[2];
		info[0].Type = ChannelType::Gray;
		info[1].Type = ChannelType::Alpha;
		output->SetChannels(info, comp);
	}
	else if (comp == 3)
	{
		ChannelInfo info[3];
		info[0].Type = ChannelType::Red;
		info[1].Type = ChannelType::Green;
		info[2].Type = ChannelType::Blue;
		output->SetChannels(info, comp);
	}
	else if (comp == 4)
	{
		ChannelInfo info[4];
		info[0].Type = ChannelType::Red;
		info[1].Type = ChannelType::Green;
		info[2].Type = ChannelType::Blue;
		info[3].Type = ChannelType::Alpha;
		output->SetChannels(info, comp);
	}

	output->CreateDefaults();
	return true;
}