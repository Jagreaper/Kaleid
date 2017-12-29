#pragma once

#include "stdafx.hpp"

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
		ChannelType Type;
	};

	class KALEID_IMAGING_API Channel
	{
	public:
		Channel(unsigned char* data, ChannelInfo channel_info);

		unsigned char GetCodeValue();
		double GetDecimalValue();
	private:
		unsigned char* _data;
		ChannelInfo _channel_info;
	};
}