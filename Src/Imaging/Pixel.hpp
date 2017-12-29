#pragma once

#include "stdafx.hpp"
#include "Channel.hpp"
#include <vector>

namespace Kaleid::Imaging
{
	class KALEID_IMAGING_API Pixel
	{
	public:
		Pixel(unsigned char* data, unsigned int data_length, ChannelInfo* channels, unsigned int num_channels);

		Channel GetChannel(unsigned int channel);
		Channel GetChannel(ChannelType channel);
	private:
		ChannelInfo* _channels;
		unsigned char* _data;

		unsigned int _num_channels;
		unsigned int _data_length;
	};
}