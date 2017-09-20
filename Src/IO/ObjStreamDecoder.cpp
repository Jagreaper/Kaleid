#include "stdafx.hpp"
#include "ObjStreamDecoder.hpp"
#include "GraphicsFactory.hpp"
#include "Model.hpp"
#include "StringHelper.hpp"
#include "Vertex.hpp"
#include <string>

using namespace Kaleid::IO;
using namespace Kaleid::Math;
using namespace Kaleid::Geometry;
using namespace Kaleid::Graphics;
using namespace Kaleid::Helpers;

bool ObjStreamDecoder::TryDecode(std::istream& source, Kaleid::Game::Model* output, Kaleid::Graphics::GraphicsFactory* arg)
{
	std::vector<Vector3f> verticies;
	std::vector<Vector3f> normals;
	std::vector<Vector2f> texels;

	std::string line;
	while (std::getline(source, line))
	{
		if (StringHelper::BeginsWith(line, std::string("v ")))
		{
			std::string nline = line.substr(2, line.size() - 2);
			std::vector<std::string> strings = StringHelper::Split(nline, ' ');
			verticies.push_back(Vector3f(std::stof(strings[0]), std::stof(strings[1]), std::stof(strings[2])));
			continue;
		}

		if (StringHelper::BeginsWith(line, std::string("vn ")))
		{
			std::string nline = line.substr(3, line.size() - 3);
			std::vector<std::string> strings = StringHelper::Split(nline, ' ');
			normals.push_back(Vector3f(std::stof(strings[0]), std::stof(strings[1]), std::stof(strings[2])));
			continue;
		}

		if (StringHelper::BeginsWith(line, std::string("vt ")))
		{
			std::string nline = line.substr(3, line.size() - 3);
			std::vector<std::string> strings = StringHelper::Split(nline, ' ');
			texels.push_back(Vector2f(std::stof(strings[0]), std::stof(strings[1])));
			continue;
		}
	}

	return false;
}