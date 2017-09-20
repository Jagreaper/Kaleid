#include "stdafx.hpp"
#include "ObjStreamDecoder.hpp"
#include "GraphicsFactory.hpp"
#include "Model.hpp"
#include "StringHelper.hpp"
#include "Vector.hpp"
#include "Vertex.hpp"
#include "Face.hpp"
#include <string>
#include <stdexcept>

using namespace Kaleid::IO;
using namespace Kaleid::Math;
using namespace Kaleid::Game;
using namespace Kaleid::Geometry;
using namespace Kaleid::Graphics;
using namespace Kaleid::Helpers;

struct ObjData
{
	std::vector<Vector3F> Verticies;
	std::vector<Vector3F> Normals;
	std::vector<Vector2F> Texels;

	std::vector<std::vector<Vector3<unsigned long>>> IndexedFaces;
};

bool TryReadVertex(std::string& line, ObjData& data)
{
	std::string nline = line.substr(2, line.size() - 2);
	std::vector<std::string> strings = StringHelper::Split(nline, ' ');
	data.Verticies.push_back(Vector3F(std::stof(strings[0]), std::stof(strings[1]), std::stof(strings[2])));
	return true;
}

bool TryReadNormal(std::string& line, ObjData& data)
{
	std::string nline = line.substr(3, line.size() - 3);
	std::vector<std::string> strings = StringHelper::Split(nline, ' ');
	data.Normals.push_back(Vector3F(std::stof(strings[0]), std::stof(strings[1]), std::stof(strings[2])));
	return true;
}

bool TryReadTexel(std::string& line, ObjData& data)
{
	std::string nline = line.substr(3, line.size() - 3);
	std::vector<std::string> strings = StringHelper::Split(nline, ' ');
	data.Texels.push_back(Vector2F(std::stof(strings[0]), std::stof(strings[1])));
	return true;
}


bool TryReadFace(std::string& line, ObjData& data)
{
	std::string nline = line.substr(2, line.size() - 2);
	std::vector<std::string> face_strings = StringHelper::Split(nline, ' ');

	std::vector<Vector3<unsigned long>>	indexed_face;
	for (int face_index = 0; face_index < face_strings.size(); face_index++)
	{
		Vector3<unsigned long> vertex;
		std::vector<std::string> vert_strings = StringHelper::Split(face_strings[face_index], '/');
		for (int type_index = 0; type_index < vert_strings.size(); type_index++)
		{
			switch (type_index)
			{
			case 0:
				vertex.x = std::stoul(vert_strings[type_index]);
				break;
			case 1:
				vertex.y = std::stoul(vert_strings[type_index]);
				break;
			case 2:
				vertex.z = std::stoul(vert_strings[type_index]);
				break;
			default:
				return false;
			}

			indexed_face.push_back(vertex);
		}
	}

	data.IndexedFaces.push_back(indexed_face);
	return true;
}

bool TryReadLine(std::string& line, ObjData& data)
{
	if (StringHelper::BeginsWith(line, std::string("v ")))
		return TryReadVertex(line, data);

	if (StringHelper::BeginsWith(line, std::string("vn ")))
		return TryReadNormal(line, data);

	if (StringHelper::BeginsWith(line, std::string("vt ")))
		return TryReadTexel(line, data);

	if (StringHelper::BeginsWith(line, std::string("f ")))
		return TryReadFace(line, data);

	return true;
}

bool BuildModel(ObjData& data, Model* model)
{
	return false;
}

bool ObjStreamDecoder::TryDecode(std::istream& source, Kaleid::Game::Model* output, Kaleid::Graphics::GraphicsFactory* arg)
{
	ObjData data;

	std::string line;
	while (std::getline(source, line))
	{
		if (!TryReadLine(line, data))
		{
			std::string msg("Could not read line:\n");
			msg += line;
			throw std::runtime_error(msg);
		}
	}

	if (!BuildModel(data, output))
		throw std::runtime_error("Could not build model");

	return false;
}