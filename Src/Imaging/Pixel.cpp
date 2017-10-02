#include "stdafx.hpp"
#include "Pixel.hpp"

using namespace Kaleid::Imaging;

Pixel::Pixel(char* data, unsigned int data_length, ChannelInfo* channels, unsigned int num_channels)
{
	this->_data = data;
	this->_data_length = data_length;
	this->_channels = channels;
	this->_num_channels = num_channels;
}

Channel Pixel::GetChannel(unsigned int channel)
{
	unsigned int offset = 0;
	for (int index = 0; index < channel; index++)
		offset += this->_channels[index].Length;

	unsigned int length = this->_channels[channel].Length;

	return Channel(this->_data + offset, length, this->_channels[channel]);
}