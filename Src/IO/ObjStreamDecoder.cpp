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
using namespace Kaleid::Geometry;
using namespace Kaleid::Graphics;
using namespace Kaleid::Helpers;

bool ObjStreamDecoder::TryDecode(std::istream& source, Kaleid::Game::Model* output, Kaleid::Graphics::GraphicsFactory* arg)
{
	std::vector<Vector3F> verticies;
	std::vector<Vector3F> normals;
	std::vector<Vector2F> texels;

	std::vector<std::vector<Vector3<unsigned long>>> indexed_faces;

	std::string line;
	while (std::getline(source, line))
	{
		if (StringHelper::BeginsWith(line, std::string("v ")))
		{
			std::string nline = line.substr(2, line.size() - 2);
			std::vector<std::string> strings = StringHelper::Split(nline, ' ');
			verticies.push_back(Vector3F(std::stof(strings[0]), std::stof(strings[1]), std::stof(strings[2])));
			continue;
		}

		if (StringHelper::BeginsWith(line, std::string("vn ")))
		{
			std::string nline = line.substr(3, line.size() - 3);
			std::vector<std::string> strings = StringHelper::Split(nline, ' ');
			normals.push_back(Vector3F(std::stof(strings[0]), std::stof(strings[1]), std::stof(strings[2])));
			continue;
		}

		if (StringHelper::BeginsWith(line, std::string("vt ")))
		{
			std::string nline = line.substr(3, line.size() - 3);
			std::vector<std::string> strings = StringHelper::Split(nline, ' ');
			texels.push_back(Vector2F(std::stof(strings[0]), std::stof(strings[1])));
			continue;
		}


		if (StringHelper::BeginsWith(line, std::string("f ")))
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
						throw new std::exception("Obj file exceeds maximum number of face index's");
					}

					indexed_face.push_back(vertex);
				}
			}

			indexed_faces.push_back(indexed_face);
			continue;
		}
	}

	return false;
}