#pragma once

#include "stdafx.hpp"

namespace Kaleid::IO
{
	template<class SourceType, class ArgumentType, class OutputType>
	class KALEID_IO_API DecoderBase abstract
	{
	public:
		virtual bool TryDecode(SourceType source, OutputType* output, ArgumentType* arg = NULL) = 0;
	};
}