#include "stdafx.hpp"
#include "Image.hpp"

using namespace Kaleid::Imaging;

Image::Image(unsigned int width, unsigned int height)
{
	this->_width = width;
	this->_height = height;
}

Image::Image(char* data, unsigned int data_length, ChannelInfo* channels, unsigned int num_channels, unsigned int width, unsigned int height)
	: Image(width, height)
{
	for (int index = 0; index < data_length; index++)
		this->_data.push_back(*data++);

	for (int index = 0; index < num_channels; index++)
		this->_channels.push_back(*channels++);

	this->CreateDefaults();
}

Image::Image(char* data, unsigned int data_length, std::vector<ChannelInfo> channels, unsigned int width, unsigned int height)
	: Image(width, height)
{
	for (int index = 0; index < data_length; index++)
		this->_data.push_back(*data++);

	this->_channels = channels;

	this->CreateDefaults();
}

Image::Image(std::vector<char> data, ChannelInfo* channels, unsigned int num_channels, unsigned int width, unsigned int height)
	: Image(width, height)
{
	this->_data = data;

	for (int index = 0; index < num_channels; index++)
		this->_channels.push_back(*channels++);

	this->CreateDefaults();
}

Image::Image(std::vector<char> data, std::vector<ChannelInfo> channels, unsigned int width, unsigned int height)
	: Image(width, height)
{
	this->_data = data;
	this->_channels = channels;

	this->CreateDefaults();
}

void Image::CreateDefaults()
{
	this->_pixel_length = ((this->_width * this->_height) / this->_data.size());
	this->_stride = this->_pixel_length * this->_width;
}

Pixel Image::GetPixel(unsigned int x, unsigned int y)
{
	if (x >= this->_width || y >= this->_height)
		throw std::runtime_error("Arguement out of bounds");

	unsigned int pos = x + (y * this->_stride);
	char* pixel_data = this->_data.data() + pos;

	return Pixel(pixel_data, this->_pixel_length, this->_channels.data(), this->_channels.size());
}