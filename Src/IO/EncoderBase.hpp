#pragma once

#include "stdafx.hpp"

namespace Kaleid::IO
{
	template<class SourceType, class ArgumentType, class InputType>
	class KALEID_IO_API EncoderBase abstract
	{
	public:
		virtual bool TryEncode(SourceType source, InputType* input, ArgumentType* arg = NULL) = 0;
	};
}