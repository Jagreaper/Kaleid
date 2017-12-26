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
		Image(unsigned char* data, unsigned int data_length, ChannelInfo* channels, unsigned int num_channels, unsigned int width, unsigned int height);
		Image(unsigned char* data, unsigned int data_length, std::vector<ChannelInfo> channels, unsigned int width, unsigned int height);
		Image(std::vector<unsigned char> data, ChannelInfo* channels, unsigned int num_channels, unsigned int width, unsigned int height);
		Image(std::vector<unsigned char> data, std::vector<ChannelInfo> channels, unsigned int width, unsigned int height);

		Pixel GetPixel(unsigned int x, unsigned int y);
		unsigned int& GetWidth();
		unsigned int& GetHeight();
		void GetSize(unsigned int* width, unsigned int* height);

		void SetData(unsigned char* data, unsigned int data_length);
		void SetData(std::vector<unsigned char> data);

		void SetChannels(ChannelInfo* channels, unsigned int num_channels);
		void SetChannels(std::vector<ChannelInfo> channels);

		void SetWidth(unsigned int width);
		void SetHeight(unsigned int height);
		void SetSize(unsigned int width, unsigned int height);

		void CreateDefaults();
	private:

		std::vector<ChannelInfo> _channels;
		std::vector<unsigned char> _data;
		unsigned int _width;
		unsigned int _height;
		unsigned int _stride;
		unsigned int _pixel_length;
	};
}
API_END