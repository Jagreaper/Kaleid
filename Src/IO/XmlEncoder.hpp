#pragma once

#include "stdafx.hpp"
#include "XmlFile.hpp"
#include "EncoderBase.hpp"

namespace Kaleid::IO
{
	class KALEID_IO_API XmlStreamEncoder : StreamEncoderBase<Kaleid::Xml::XmlFile*, void*>
	{
	public:
		bool TryEncode(std::ostream& source, Kaleid::Xml::XmlFile* input, void* arg);
	};

	class KALEID_IO_API XmlPathEncoder : PathEncoderBase<Kaleid::Xml::XmlFile*, void*>
	{
	public:
		bool TryEncode(const char* source, Kaleid::Xml::XmlFile* input, void* arg);
	private:
		XmlStreamEncoder _stream_encoder;;
	};
}