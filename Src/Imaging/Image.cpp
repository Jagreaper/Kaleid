#include "stdafx.hpp"
#include "Image.hpp"

using namespace Kaleid::Imaging;


Image::Image(int byte_size)
{
	this->_data = new char[(this->_byte_size = byte_size)];
}

Image::~Image()
{
	delete[] this->_data;
}