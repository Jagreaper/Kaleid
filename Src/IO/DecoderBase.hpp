#pragma once

#include "stdafx.hpp"

namespace Kaleid::IO
{
	template<class SourceType, class OutputType, class ArgumentType>
	class KALEID_IO_API DecoderBase
	{
	public:
		virtual bool TryDecode(SourceType source, OutputType output, ArgumentType arg = NULL) = 0;
	};
}