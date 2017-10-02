#pragma once

#include "stdafx.hpp"
#include "Channel.hpp"
#include "Pixel.hpp"
#include <vector>

API_BEGIN
namespace Kaleid::Imaging
{
	class KALEID_IMAGING_API Image
	{
	public:
		Image();
		Image(char* data, unsigned int data_length, ChannelInfo* channels, unsigned int num_channels, unsigned int width, unsigned int height);
		Image(char* data, unsigned int data_length, std::vector<ChannelInfo> channels, unsigned int width, unsigned int height);
		Image(std::vector<char> data, ChannelInfo* channels, unsigned int num_channels, unsigned int width, unsigned int height);
		Image(std::vector<char> data, std::vector<ChannelInfo> channels, unsigned int width, unsigned int height);

		Pixel GetPixel(unsigned int x, unsigned int y);
	private:
		Image(unsigned int width, unsigned int height);
		
		void CreateDefaults();

		std::vector<ChannelInfo> _channels;
		std::vector<char> _data;
		unsigned int _width;
		unsigned int _height;
		unsigned int _stride;
		unsigned int _pixel_length;
	};
}
API_END