#pragma once

#include "stdafx.hpp"
#include <ostream>

namespace Kaleid::IO
{
	template<class SourceType, class InputType, class ArgumentType>
	class KALEID_IO_API EncoderBase
	{
	public:
		virtual bool TryEncode(SourceType source, InputType input, ArgumentType arg = NULL) = 0;
	};

	template<class InputType, class ArgumentType>
	using StreamEncoderBase = EncoderBase<std::ostream&, InputType, ArgumentType>;

	template<class InputType, class ArgumentType>
	using PathEncoderBase = EncoderBase<const char*, InputType, ArgumentType>;
}