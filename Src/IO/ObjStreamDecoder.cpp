#include "stdafx.hpp"
#include "ObjStreamDecoder.hpp"
#include "GraphicsFactory.hpp"
#include "Model.hpp"
#include "StringHelper.hpp"
#include "Vector.hpp"
#include "Vertex.hpp"
#include "Triangle.hpp"
#include "Face.hpp"
#include "Mesh.hpp"
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

bool TesselateFaces(std::vector<FaceF>* baked_faces, std::vector<FaceF>* tess_faces)
{
	for (int face_index = 0; face_index < baked_faces->size(); face_index++)
	{
		FaceF face = baked_faces->at(face_index);

		int length = face.GetVerticies().size() - 2;
		VertexF origin = face.GetVerticies()[0];

		for (int index = 0; index < length; index++)
		{
			VertexF v1 = face.GetVerticies()[1 + index];
			VertexF v2 = face.GetVerticies()[2 + index];
			tess_faces->push_back(Triangle(origin, v1, v2));
		}
	}

	return true;
}

struct MeshData
{
	std::vector<float> Verticies;
	std::vector<float> Normals;
	std::vector<float> Texels;
	std::vector<unsigned int> Indicies;
};

void AddVertexData(MeshData* data, FaceF& face)
{
	VertexF v1 = face.GetVerticies()[0];
	VertexF v2 = face.GetVerticies()[1];
	VertexF v3 = face.GetVerticies()[2];

	if (!v1.VectorGeometry.IsNull())
	{
		data->Verticies.push_back(v1.VectorGeometry.GetValue().x);
		data->Verticies.push_back(v1.VectorGeometry.GetValue().y);
		data->Verticies.push_back(v1.VectorGeometry.GetValue().z);
	}

	if (!v2.VectorGeometry.IsNull())
	{
		data->Verticies.push_back(v2.VectorGeometry.GetValue().x);
		data->Verticies.push_back(v2.VectorGeometry.GetValue().y);
		data->Verticies.push_back(v2.VectorGeometry.GetValue().z);
	}

	if (!v3.VectorGeometry.IsNull())
	{
		data->Verticies.push_back(v3.VectorGeometry.GetValue().x);
		data->Verticies.push_back(v3.VectorGeometry.GetValue().y);
		data->Verticies.push_back(v3.VectorGeometry.GetValue().z);
	}

	if (!v1.VectorNormal.IsNull())
	{
		data->Normals.push_back(v1.VectorNormal.GetValue().x);
		data->Normals.push_back(v1.VectorNormal.GetValue().y);
		data->Normals.push_back(v1.VectorNormal.GetValue().z);
	}

	if (!v2.VectorNormal.IsNull())
	{
		data->Normals.push_back(v2.VectorNormal.GetValue().x);
		data->Normals.push_back(v2.VectorNormal.GetValue().y);
		data->Normals.push_back(v2.VectorNormal.GetValue().z);
	}

	if (!v3.VectorNormal.IsNull())
	{
		data->Normals.push_back(v3.VectorNormal.GetValue().x);
		data->Normals.push_back(v3.VectorNormal.GetValue().y);
		data->Normals.push_back(v3.VectorNormal.GetValue().z);
	}

	if (!v1.VectorTexture.IsNull())
	{
		data->Texels.push_back(v1.VectorTexture.GetValue().x);
		data->Texels.push_back(v1.VectorTexture.GetValue().y);
	}

	if (!v2.VectorTexture.IsNull())
	{
		data->Texels.push_back(v2.VectorTexture.GetValue().x);
		data->Texels.push_back(v2.VectorTexture.GetValue().y);
	}

	if (!v3.VectorTexture.IsNull())
	{
		data->Texels.push_back(v3.VectorTexture.GetValue().x);
		data->Texels.push_back(v3.VectorTexture.GetValue().y);
	}
}

bool TryBuildMeshData(MeshData* data, std::vector<FaceF>* baked_faces)
{
	for (int index = 0; index < baked_faces->size(); index++)
	{
		AddVertexData(data, baked_faces->at(index));

		unsigned int offset = index * 3;
		data->Indicies.push_back(offset);
		data->Indicies.push_back(offset + 1);
		data->Indicies.push_back(offset + 2);
	}

	return true;
}

bool TryBuildMesh(MeshData* data, Mesh* mesh, GraphicsFactory* arg)
{
	VertexBuffer* vbo = arg->CreateVertexBuffer(&data->Verticies[0], data->Verticies.size(), 3);
	VertexBuffer* nbo = arg->CreateVertexBuffer(&data->Normals[0], data->Normals.size(), 3);
	VertexBuffer* tbo = arg->CreateVertexBuffer(&data->Texels[0], data->Texels.size(), 2);
	IndexBuffer* ibo = arg->CreateIndexBuffer(&data->Indicies[0], data->Indicies.size());

	std::vector<VertexBuffer*> buffers;
	buffers.push_back(vbo);
	buffers.push_back(nbo);
	buffers.push_back(tbo);

	mesh->SetVertexBuffers(&buffers);
	mesh->SetIndexBuffer(ibo);
	mesh->SetPrimitiveType(PrimitiveType::Triangles);
	mesh->Compose();

	return true;
}

bool ObjStreamDecoder::TryDecode(std::istream& source, Model* output, GraphicsFactory* arg)
{
	ObjData data;
	{
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
	}

	Mesh* mesh = arg->CreateMesh();
	{
		MeshData mesh_data;
		{
			std::vector<FaceF> tess_faces;
			{
				std::vector<FaceF> baked_faces;
				if (!BakeFaces(data, &baked_faces))
					throw std::runtime_error("Could not bake faces");

				if (!TesselateFaces(&baked_faces, &tess_faces))
					throw std::runtime_error("Could not tesselate faces");
			}

			if (!TryBuildMeshData(&mesh_data, &tess_faces))
				throw std::runtime_error("Could not build mesh");
		}

		if (!TryBuildMesh(&mesh_data, mesh, arg))
			throw std::runtime_error("Could build mesh");
	}

	output->AddMesh(mesh);
	return true;
}