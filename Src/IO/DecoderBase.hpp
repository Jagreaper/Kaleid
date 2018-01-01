#pragma once

#include "stdafx.hpp"
#include <istream>

namespace Kaleid::IO
{
	template<class SourceType, class OutputType, class ArgumentType>
	class KALEID_IO_API DecoderBase
	{
	public:
		virtual bool TryDecode(SourceType source, OutputType output, ArgumentType arg = NULL) = 0;
	};

	template<class OutputType, class ArgumentType>
	using StreamDecoderBase = DecoderBase<std::istream&, OutputType, ArgumentType>;

	template<class OutputType, class ArgumentType>
	using PathDecoderBase = DecoderBase<const char*, OutputType, ArgumentType>;
}