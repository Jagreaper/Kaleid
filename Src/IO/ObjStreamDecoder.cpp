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

	std::vector<std::vector<std::vector<unsigned long>>> IndexedFaces;
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

	std::vector<std::vector<unsigned long>>	indexed_face;
	for (int face_index = 0; face_index < face_strings.size(); face_index++)
	{
		std::vector<unsigned long> vertex;
		std::vector<std::string> vert_strings = StringHelper::Split(face_strings[face_index], '/');

		for (int type_index = 0; type_index < vert_strings.size(); type_index++)
			vertex.push_back(std::stoul(vert_strings[type_index]));

		indexed_face.push_back(vertex);
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

bool TesselateFaces(std::vector<FaceF>* faces)
{
	std::vector<FaceF> tess_faces;
	for (int face_index = 0; face_index < faces->size(); faces++)
	{
		FaceF face = faces->at(face_index);

		int length = face.GetVerticies().size() - 2;
		VertexF origin = face.GetVerticies()[0];

		for (int index = 0; index < length; index++)
		{
			// TODO: Tesslate Verticies;
		}
	}

	return false;
}

bool BakeFaces(ObjData& data, std::vector<FaceF>* faces)
{
	for (int face_index = 0; face_index < data.IndexedFaces.size(); face_index++)
	{
		FaceF face;
		for (int vert_index = 0; vert_index < data.IndexedFaces[face_index].size(); vert_index++)
		{
			VertexF vertex;
			for (int type_index = 0; type_index < data.IndexedFaces[face_index][vert_index].size(); type_index++)
			{
				switch (type_index)
				{
				case 0:
					vertex.VectorGeometry = data.Verticies[data.IndexedFaces[face_index][vert_index][type_index] - 1];
					break;
				case 1:
					vertex.VectorTexture = data.Texels[data.IndexedFaces[face_index][vert_index][type_index] - 1];
					break;
				case 2:
					vertex.VectorNormal = data.Normals[data.IndexedFaces[face_index][vert_index][type_index] - 1];
					break;
				default:
					return false;
				}
			}

			face.AddVerticies(vertex);
		}

		faces->push_back(face);
	}

	return true;
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

	std::vector<FaceF> faces;
	if (!BakeFaces(data, &faces))
		throw std::runtime_error("Could not bake faces");

	if (!TesselateFaces(&faces))
		throw std::runtime_error("Could not tesselate faces");

	return false;
}