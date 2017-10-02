#include "stdafx.hpp"
#include "Channel.hpp"
#include <math.h>

using namespace Kaleid::Imaging;

Channel::Channel(char* data, unsigned char data_length, ChannelInfo channel_info)
{
	this->_data = data;
	this->_data_length = data_length > 8 ? 8 : data_length;
	this->_channel_info = channel_info;
}

unsigned long long Channel::GetRealValue()
{
	unsigned long long value = 0;
	for (int index = 0; index < this->_data_length; index++)
		value = value | (this->_data[index] << (index * 8));

	return value;
}

double Channel::GetDecimalValue()
{
	double real_value = (double)this->GetRealValue();
	double max_value = pow(2, this->_data_length);
	return real_value / max_value;
}