#include "ObjModelDecoder.hpp"
#include "Kaleid.Graphics\GraphicsFactory.hpp"
#include "Kaleid.Game\Model.hpp"
#include "Jagerts.Felcp.Helpers\StringHelper.hpp"
#include "Jagerts.Felcp.Helpers\VectorHelper.hpp"
#include "Kaleid.Math\Vector.hpp"
#include "Kaleid.Geometry\Vertex.hpp"
#include "Kaleid.Geometry\Triangle.hpp"
#include "Kaleid.Geometry\Face.hpp"
#include "Kaleid.Graphics\Mesh.hpp"
#include "Kaleid.Graphics\Material.hpp"
#include <string>
#include <stdexcept>
#include <limits>
#include <iostream>
#include <fstream>

using namespace Kaleid::IO;
using namespace Kaleid::Math;
using namespace Kaleid::Game;
using namespace Kaleid::Geometry;
using namespace Kaleid::Graphics;
using namespace Jagerts::Felcp::Helpers;

struct ObjPieceData
{
	std::string GroupName;
	std::string ObjectName;
	std::string MaterialName;
	std::vector<std::vector<std::vector<unsigned long>>> IndexedFaces;
};

struct ObjData
{
	std::vector<Vector3F> Verticies;
	std::vector<Vector3F> Normals;
	std::vector<Vector2F> Texels;

	Vector3F VertexMax = Vector3F(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min());
	Vector3F VertexMin = Vector3F(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());

	std::vector<ObjPieceData> pieces;
};

bool TryReadVertex(std::string& line, ObjData& data)
{
	std::vector<std::string> strings = StringHelper::Split(line, ' ');
	Vector3F vec = Vector3F(std::stof(strings[1]), std::stof(strings[2]), std::stof(strings[3]));

	data.VertexMax.x = vec.x > data.VertexMax.x ? vec.x : data.VertexMax.x;
	data.VertexMax.y = vec.y > data.VertexMax.y ? vec.y : data.VertexMax.y;
	data.VertexMax.z = vec.z > data.VertexMax.z ? vec.z : data.VertexMax.z;

	data.VertexMin.x = vec.x < data.VertexMin.x ? vec.x : data.VertexMin.x;
	data.VertexMin.y = vec.y < data.VertexMin.y ? vec.y : data.VertexMin.y;
	data.VertexMin.z = vec.z < data.VertexMin.z ? vec.z : data.VertexMin.z;

	data.Verticies.push_back(vec);
	return true;
}

bool TryReadNormal(std::string& line, ObjData& data)
{
	std::vector<std::string> strings = StringHelper::Split(line, ' ');
	data.Normals.push_back(Vector3F(std::stof(strings[1]), std::stof(strings[2]), std::stof(strings[3])));
	return true;
}

bool TryReadTexel(std::string& line, ObjData& data)
{
	std::vector<std::string> strings = StringHelper::Split(line, ' ');
	data.Texels.push_back(Vector2F(std::stof(strings[1]), std::stof(strings[2])));
	return true;
}

bool TryReadFace(std::string& line, ObjPieceData& piece)
{
	std::vector<std::string> face_strings = StringHelper::Split(line, ' ');

	std::vector<std::vector<unsigned long>>	indexed_face;
	for (unsigned int face_index = 1; face_index < (unsigned int)face_strings.size(); face_index++)
	{
		std::vector<unsigned long> vertex;
		std::vector<std::string> vert_strings = StringHelper::Split(face_strings[face_index], '/');
		for (unsigned int type_index = 0; type_index < (unsigned int)vert_strings.size(); type_index++)
			vertex.push_back(std::stoul(vert_strings[type_index]));

		indexed_face.push_back(vertex);
	}

	piece.IndexedFaces.push_back(indexed_face);
	return true;
}

bool TryReadLine(std::string& line, ObjData& data, ObjPieceData& piece)
{
	if (StringHelper::BeginsWith(line, std::string("v ")))
		return TryReadVertex(line, data);

	if (StringHelper::BeginsWith(line, std::string("vn ")))
		return TryReadNormal(line, data);

	if (StringHelper::BeginsWith(line, std::string("vt ")))
		return TryReadTexel(line, data);

	if (StringHelper::BeginsWith(line, std::string("f ")))
		return TryReadFace(line, piece);

	return true;
}

bool NormalizeVerticies(ObjData& data)
{
	Vector3F diff = (data.VertexMax - data.VertexMin) / 2.0f;
	Vector3F offset = -data.VertexMin - diff;

	for (int index = 0; index < data.Verticies.size(); index++)
		data.Verticies[index] = (data.Verticies[index] + offset) / diff;

	return true;
}

bool CenterVerticies(ObjData& data)
{
	Vector3F diff = (data.VertexMax - data.VertexMin) / 2.0f;
	Vector3F offset = -data.VertexMin - diff;

	for (int index = 0; index < data.Verticies.size(); index++)
		data.Verticies[index] = (data.Verticies[index] + offset);

	return true;
}

bool BakeFaces(ObjData& data, ObjPieceData& piece, std::vector<FaceF>& faces)
{
	for (unsigned int face_index = 0; face_index < (unsigned int)piece.IndexedFaces.size(); face_index++)
	{
		FaceF face;
		for (unsigned int vert_index = 0; vert_index < (unsigned int)piece.IndexedFaces[face_index].size(); vert_index++)
		{
			VertexF vertex;
			for (unsigned int type_index = 0; type_index < (unsigned int)piece.IndexedFaces[face_index][vert_index].size(); type_index++)
			{
				switch (type_index)
				{
				case 0:
					vertex.VectorGeometry = data.Verticies[piece.IndexedFaces[face_index][vert_index][type_index] - 1];
					break;
				case 1:
					vertex.VectorTexture = data.Texels[piece.IndexedFaces[face_index][vert_index][type_index] - 1];
					break;
				case 2:
					vertex.VectorNormal = data.Normals[piece.IndexedFaces[face_index][vert_index][type_index] - 1];
					break;
				default:
					return false;
				}
			}

			face.AddVerticies(vertex);
		}

		faces.push_back(face);
	}

	return true;
}

bool TesselateFaces(std::vector<FaceF>& baked_faces, std::vector<FaceF>& tess_faces)
{
	for (unsigned int face_index = 0; face_index < (unsigned int)baked_faces.size(); face_index++)
	{
		FaceF face = baked_faces[face_index];

		int length = face.GetVerticies().size() - 2;
		VertexF origin = face.GetVerticies()[0];

		for (int index = 0; index < length; index++)
		{
			VertexF v1 = face.GetVerticies()[1 + index];
			VertexF v2 = face.GetVerticies()[2 + index];
			tess_faces.push_back(Triangle(origin, v1, v2));
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

void AddVerticies(MeshData& data, VertexF& v1, VertexF& v2, VertexF& v3)
{
	if (!v1.VectorGeometry.IsNull())
	{
		data.Verticies.push_back(v1.VectorGeometry.GetValue().x);
		data.Verticies.push_back(v1.VectorGeometry.GetValue().y);
		data.Verticies.push_back(v1.VectorGeometry.GetValue().z);
	}

	if (!v2.VectorGeometry.IsNull())
	{
		data.Verticies.push_back(v2.VectorGeometry.GetValue().x);
		data.Verticies.push_back(v2.VectorGeometry.GetValue().y);
		data.Verticies.push_back(v2.VectorGeometry.GetValue().z);
	}

	if (!v3.VectorGeometry.IsNull())
	{
		data.Verticies.push_back(v3.VectorGeometry.GetValue().x);
		data.Verticies.push_back(v3.VectorGeometry.GetValue().y);
		data.Verticies.push_back(v3.VectorGeometry.GetValue().z);
	}
}

void AddNormals(MeshData& data, VertexF& v1, VertexF& v2, VertexF& v3)
{
	if (!v1.VectorNormal.IsNull())
	{
		data.Normals.push_back(v1.VectorNormal.GetValue().x);
		data.Normals.push_back(v1.VectorNormal.GetValue().y);
		data.Normals.push_back(v1.VectorNormal.GetValue().z);
	}

	if (!v2.VectorNormal.IsNull())
	{
		data.Normals.push_back(v2.VectorNormal.GetValue().x);
		data.Normals.push_back(v2.VectorNormal.GetValue().y);
		data.Normals.push_back(v2.VectorNormal.GetValue().z);
	}

	if (!v3.VectorNormal.IsNull())
	{
		data.Normals.push_back(v3.VectorNormal.GetValue().x);
		data.Normals.push_back(v3.VectorNormal.GetValue().y);
		data.Normals.push_back(v3.VectorNormal.GetValue().z);
	}
}

void AddTexels(MeshData& data, VertexF& v1, VertexF& v2, VertexF& v3)
{
	if (!v1.VectorTexture.IsNull())
	{
		data.Texels.push_back(v1.VectorTexture.GetValue().x);
		data.Texels.push_back(1.0f - v1.VectorTexture.GetValue().y);
	}

	if (!v2.VectorTexture.IsNull())
	{
		data.Texels.push_back(v2.VectorTexture.GetValue().x);
		data.Texels.push_back(1.0f - v2.VectorTexture.GetValue().y);
	}

	if (!v3.VectorTexture.IsNull())
	{
		data.Texels.push_back(v3.VectorTexture.GetValue().x);
		data.Texels.push_back(1.0f - v3.VectorTexture.GetValue().y);
	}
}

void AddVertexData(MeshData& data, FaceF& face)
{
	VertexF v1 = face.GetVerticies()[0];
	VertexF v2 = face.GetVerticies()[1];
	VertexF v3 = face.GetVerticies()[2];

	AddVerticies(data, v1, v2, v3);
	AddNormals(data, v1, v2, v3);
	AddTexels(data, v1, v2, v3);
}

bool TryBuildMeshData(MeshData& data, std::vector<FaceF>& baked_faces)
{
	for (unsigned int index = 0; index < (unsigned int)baked_faces.size(); index++)
	{
		AddVertexData(data, baked_faces[index]);

		unsigned int offset = index * 3;
		data.Indicies.push_back(offset);
		data.Indicies.push_back(offset + 1);
		data.Indicies.push_back(offset + 2);
	}

	return true;
}

bool TryBuildMesh(MeshData& data, Mesh*& mesh, GraphicsFactory*& arg)
{
	VertexBuffer* vbo = arg->CreateVertexBuffer(data.Verticies.size() != 0 ? &data.Verticies[0] : NULL, data.Verticies.size(), 3);
	VertexBuffer* nbo = arg->CreateVertexBuffer(data.Normals.size() != 0 ? &data.Normals[0] : NULL, data.Normals.size(), 3);
	VertexBuffer* tbo = arg->CreateVertexBuffer(data.Texels.size() != 0 ? &data.Texels[0] : NULL, data.Texels.size(), 2);
	IndexBuffer* ibo = arg->CreateIndexBuffer(data.Indicies.size() != 0 ? &data.Indicies[0] : NULL, data.Indicies.size());

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

bool TryReadLines(std::istream& source, ObjData& data, std::vector<ObjPieceData>& pieces)
{
	ObjPieceData piece;
	bool found_piece = false;
	std::string line;
	while (std::getline(source, line))
	{
		line = StringHelper::TrimLeading(line);

		if (StringHelper::BeginsWith(line, std::string("o ")))
		{
			std::string name = StringHelper::Split(line, ' ')[1];

			if (found_piece == false)
				found_piece = true;
			else if (piece.GroupName != name)
			{
				pieces.push_back(piece);
				piece = ObjPieceData();
			}

			piece.ObjectName = name;
		}
		else if (StringHelper::BeginsWith(line, std::string("g ")))
		{
			std::string name = StringHelper::Split(line, ' ')[1];

			if (found_piece == false)
				found_piece = true;
			else if (piece.ObjectName != name)
			{
				pieces.push_back(piece);
				piece = ObjPieceData();
			}

			piece.GroupName = name;
		}
		else if (StringHelper::BeginsWith(line, std::string("usemtl ")))
		{
			std::string name = StringHelper::Split(line, ' ')[1];

			if (found_piece == false)
				found_piece = true;
			else if (piece.MaterialName.length() != 0)
			{
				pieces.push_back(piece);
				piece = ObjPieceData();
			}

			piece.MaterialName = name;
		}
		else if (!TryReadLine(line, data, piece))
		{

			std::string msg("Could not read line:\n");
			msg += line;
			throw std::runtime_error(msg);
		}
	}

	return true;
}

bool TryCreateMesh(ObjData& data, ObjPieceData& piece, ModelDecoderParams& arg, Mesh*& mesh_ptr)
{
	mesh_ptr = arg.GraphicsFactory->CreateMesh();
	{
		MeshData mesh_data;
		{
			std::vector<FaceF> tess_faces;
			{
				std::vector<FaceF> baked_faces;
				if (!BakeFaces(data, piece, baked_faces))
					throw std::runtime_error("Could not bake faces");

				if (!TesselateFaces(baked_faces, tess_faces))
					throw std::runtime_error("Could not tesselate faces");
			}

			if (!TryBuildMeshData(mesh_data, tess_faces))
				throw std::runtime_error("Could not build mesh");
		}

		if (!TryBuildMesh(mesh_data, mesh_ptr, arg.GraphicsFactory))
			throw std::runtime_error("Could build mesh");
	}
}

bool TryCreateComponents(ObjData& data, std::vector<ObjPieceData>& pieces, ModelDecoderParams& arg, std::vector<ModelComponent*>& components)
{
	for (int p_index = 0; p_index < pieces.size(); p_index++)
	{
		ModelComponent* component = ModelComponent::AllocateMemory();
		Mesh* mesh;
		TryCreateMesh(data, pieces[p_index], arg, mesh);
		component->SetMesh(mesh);

		for (int m_index = 0; m_index < arg.Materials->size(); m_index++)
		{
			if (pieces[p_index].MaterialName == (*arg.Materials)[m_index].Name)
				component->SetMaterialInfo((*arg.Materials)[m_index]);
		}

		component->SetName(pieces[p_index].ObjectName.size() != 0 ? pieces[p_index].ObjectName : pieces[p_index].GroupName);
		components.push_back(component);
	}

	return true;
}

bool ObjModelDecoder::TryDecode(std::istream& source, Model* output, ModelDecoderParams& arg)
{
	std::vector<ObjPieceData> pieces;
	ObjData data;
	if (!TryReadLines(source, data, pieces))
		throw std::runtime_error("Could not read stream");

	if (arg.ModelDecoderParamsArg == ModelDecoderParamsArg::Normalize)
	{
		if (!NormalizeVerticies(data))
			throw std::runtime_error("Could not normalize verticies");
	}
	else if (arg.ModelDecoderParamsArg == ModelDecoderParamsArg::Center)
	{
		if (!CenterVerticies(data))
			throw std::runtime_error("Could not center verticies");
	}

	
	std::vector<ModelComponent*> components;
	if (!TryCreateComponents(data, pieces, arg, components))
		throw std::runtime_error("Could not create components");

	output->AddComponents(components);
	return true;
}