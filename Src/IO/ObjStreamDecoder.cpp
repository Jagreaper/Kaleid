#include "stdafx.hpp"
#include "ObjStreamDecoder.hpp"
#include "GraphicsFactory.hpp"
#include "Model.hpp"
#include "StringHelper.hpp"
#include <string>

using namespace Kaleid::IO;
using namespace Kaleid::Graphics;
using namespace Kaleid::Helpers;

bool ObjStreamDecoder::TryDecode(std::istream& source, Kaleid::Game::Model* output, Kaleid::Graphics::GraphicsFactory* arg)
{
	std::string line;
	while (std::getline(source, line))
	{
		if (StringHelper::BeginsWith(line, std::string("v ")))
		{
			std::string nline = line.substr(2, line.size() - 2);
			std::vector<std::string> strings = StringHelper::Split(nline, ' ');

			// Verticies
		}
	}

	return false;
}