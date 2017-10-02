#pragma once

#include "stdafx.hpp"
#include "Pixel.hpp"

API_BEGIN
namespace Kaleid::Imaging
{
	enum ChannelType
	{
		Red,
		Green,
		Blue,
		Alpha,
		Gray,
	};

	struct ChannelInfo
	{
		unsigned int Length;
		ChannelType Type;
	};

	class Channel
	{
	public:
		Channel(char* data, unsigned char data_length, ChannelInfo channel_info);

		unsigned long long GetRealValue();
		double GetDecimalValue();
		unsigned char GetCodeValue();
	private:
		char* _data;
		unsigned char _data_length;
		ChannelInfo _channel_info;
	};
}
API_END