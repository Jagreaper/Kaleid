#include "stdafx.hpp"
#include "PngStreamDecoder.hpp"
#include "Image.hpp"
#include "PrimitiveTypes.hpp"
#include <string>
#include <stdexcept>

using namespace Kaleid::IO;
using namespace Kaleid::Imaging;
using namespace Kaleid::Helpers;

struct PngHeader
{
	byte ByteDetect;
	char Signature[3];
	ushort DOSLineEnding;
	byte EOFChar;
	byte UnixLineEnding;
};

struct PngChunk
{
	uint Length;
	uint Type;
	std::vector<char> Data;
	uint CRC;
};

struct PngFile
{
	PngHeader Header;
	std::vector<PngChunk> Chunks;
};

void ReadHeader(std::istream& source, PngFile*& file)
{
	file->Header.ByteDetect = source.get();
	source.read(file->Header.Signature, 3);

	char dosLineEnding[2];
	source.read(dosLineEnding, 2);
	file->Header.DOSLineEnding = (dosLineEnding[0] << 8) | (dosLineEnding[1]);

	file->Header.EOFChar = (source.get());
	file->Header.UnixLineEnding = (source.get());
}

void ReadChunks(std::istream& source, PngFile*& file)
{
	while (source.peek() != EOF)
	{
		PngChunk chunk;

		char length[4];
		source.read(length, 4);
		chunk.Length = (length[0] << 24) | (length[1] << 16) | (length[2] << 8) | length[3];

		char type[4];
		source.read(type, 4);
		chunk.Type = (type[0] << 24) | (type[1] << 16) | (type[2] << 8) | type[3];

		chunk.Data.resize(chunk.Length);
		source.read(chunk.Data.data(), chunk.Length);

		char crc[4];
		source.read(crc, 4);
		chunk.CRC = (crc[0] << 24) | (crc[1] << 16) | (crc[2] << 8) | crc[3];

		file->Chunks.push_back(chunk);
	}
}

void ReadFile(std::istream& source, PngFile* file)
{
	ReadHeader(source, file);
	ReadChunks(source, file);
}

bool PngStreamDecoder::TryDecode(std::istream& source, Image* output, void* arg)
{
	PngFile file;
	ReadFile(source, &file);
	throw std::runtime_error("Not implemented");
}