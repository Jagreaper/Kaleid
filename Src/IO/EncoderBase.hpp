#pragma once

#include "stdafx.hpp"

namespace Kaleid::IO
{
	template<class SourceType, class InputType, class ArgumentType>
	class KALEID_IO_API EncoderBase abstract
	{
	public:
		virtual bool TryEncode(SourceType source, InputType* input, ArgumentType* arg = NULL) = 0;
	};
}