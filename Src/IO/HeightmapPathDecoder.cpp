#include "stdafx.hpp"
#include "HeightmapPathDecoder.hpp"
#include "GraphicsFactory.hpp"
#include "Mesh.hpp"
#include "ModelComponent.hpp"
#include "Model.hpp"
#include "Vector.hpp"
#include "ImagePathDecoder.hpp"
#include "Image.hpp"
#include <string>
#include <stdexcept>
#include <vector>

using namespace Kaleid::IO;
using namespace Kaleid::Game;
using namespace Kaleid::Math;
using namespace Kaleid::Graphics;
using namespace Kaleid::Imaging;

void AppendVertex(std::vector<float>& verticies, Vector3F& vec)
{
	verticies.push_back(vec.x);
	verticies.push_back(vec.y);
	verticies.push_back(vec.z);
}

void AppendVertex(std::vector<float>& verticies, Vector2F& vec)
{
	verticies.push_back(vec.x);
	verticies.push_back(vec.y);
}

Vector3F CalculateSurfaceNormal(Vector3F p1, Vector3F p2, Vector3F p3)
{
	Vector3F e1 = p2 - p1;
	Vector3F e2 = p3 - p1;
	return glm::normalize(glm::cross(e1, e2));
}

float GetHeight(Image& image, unsigned int x, unsigned int y)
{
	return image.GetPixel(x, y).GetChannel(0).GetCodeValue();
}

bool HeightmapPathDecoder::TryDecode(const char* source, Model* output, ModelDecoderParams& arg)
{
	Image image;
	ImagePathDecoder decoder;
	decoder.TryDecode(source, &image, NULL);

	std::vector<float> verticies;
	std::vector<float> normals;
	std::vector<float> texels;
	std::vector<unsigned int> indicies;

	unsigned int index = 0;

	float width = image.GetWidth() - 1;
	float height = image.GetHeight() - 1;

	float x_offset = width / 2.0f;
	float y_offset = height / 2.0f;
	float z_offset = 127.5f;

	for (unsigned int x = 0; x < width; x++)
	{
		for (unsigned int y = 0; x < height; y++)
		{
			Vector3F v1 = Vector3F(x, y, GetHeight(image, x, y));
			Vector3F v2 = Vector3F(x + 1, y, GetHeight(image, x + 1, y));
			Vector3F v3 = Vector3F(x, y + 1, GetHeight(image, x, y + 1));

			Vector3F v4 = v2;
			Vector3F v5 = v3;
			Vector3F v6 = Vector3F(x + 1, y + 1, GetHeight(image, x + 1, y + 1));

			if (arg.ModelDecoderParamsArg == ModelDecoderParamsArg::Center)
			{
				v1.x -= x_offset;
				v1.y -= y_offset;
				v1.z -= z_offset;
				
				v2.x -= x_offset;
				v2.y -= y_offset;
				v2.z -= z_offset;

				v3.x -= x_offset;
				v3.y -= y_offset;
				v3.z -= z_offset;

				v4.x -= x_offset;
				v4.y -= y_offset;
				v4.z -= z_offset;

				v5.x -= x_offset;
				v5.y -= y_offset;
				v5.z -= z_offset;

				v6.x -= x_offset;
				v6.y -= y_offset;
				v6.z -= z_offset;
			}
			
			if (arg.ModelDecoderParamsArg == ModelDecoderParamsArg::Normalize)
			{
				v1.x /= x_offset;
				v1.y /= y_offset;
				v1.z /= z_offset;

				v2.x /= x_offset;
				v2.y /= y_offset;
				v2.z /= z_offset;

				v3.x /= x_offset;
				v3.y /= y_offset;
				v3.z /= z_offset;

				v4.x /= x_offset;
				v4.y /= y_offset;
				v4.z /= z_offset;

				v5.x /= x_offset;
				v5.y /= y_offset;
				v5.z /= z_offset;

				v6.x /= x_offset;
				v6.y /= y_offset;
				v6.z /= z_offset;
			}

			AppendVertex(verticies, v1);
			AppendVertex(verticies, v2);
			AppendVertex(verticies, v3);

			AppendVertex(verticies, v4);
			AppendVertex(verticies, v5);
			AppendVertex(verticies, v6);

			Vector3F n1 = CalculateSurfaceNormal(v1, v2, v3);
			Vector3F n2 = CalculateSurfaceNormal(v2, v1, v3);
			Vector3F n3 = CalculateSurfaceNormal(v3, v1, v2);

			Vector3F n4 = CalculateSurfaceNormal(v4, v5, v6);
			Vector3F n5 = CalculateSurfaceNormal(v5, v4, v6);
			Vector3F n6 = CalculateSurfaceNormal(v5, v6, v4);

			AppendVertex(normals, n1);
			AppendVertex(normals, n2);
			AppendVertex(normals, n3);

			AppendVertex(normals, n4);
			AppendVertex(normals, n5);
			AppendVertex(normals, n6);

			Vector2F t1 = Vector2F(x / width, y / height);
			Vector2F t2 = Vector2F((x + 1) / width, y / height);
			Vector2F t3 = Vector2F(x / width, (y + 1) / height);

			Vector2F t4 = Vector2F((x + 1) / width, y / height);
			Vector2F t5 = Vector2F(x / width, (y + 1) / height);
			Vector2F t6 = Vector2F((x + 1) / width, (y + 1) / height);

			AppendVertex(texels, t1);
			AppendVertex(texels, t2);
			AppendVertex(texels, t3);
			
			AppendVertex(texels, t4);
			AppendVertex(texels, t5);
			AppendVertex(texels, t6);

			indicies.push_back(index++);
			indicies.push_back(index++);
			indicies.push_back(index++);

			indicies.push_back(index++);
			indicies.push_back(index++);
			indicies.push_back(index++);
		}
	}

	Mesh* mesh = arg.GraphicsFactory->CreateMesh();
	VertexBuffer* vbo = arg.GraphicsFactory->CreateVertexBuffer(&verticies[0], verticies.size(), 3);
	VertexBuffer* nbo = arg.GraphicsFactory->CreateVertexBuffer(&normals[0], normals.size(), 3);
	VertexBuffer* tbo = arg.GraphicsFactory->CreateVertexBuffer(&texels[0], texels.size(), 2);
	IndexBuffer* ibo = arg.GraphicsFactory->CreateIndexBuffer(&indicies[0], indicies.size());

	std::vector<VertexBuffer*> buffers;
	buffers.push_back(vbo);
	buffers.push_back(nbo);
	buffers.push_back(tbo);

	mesh->SetVertexBuffers(&buffers);
	mesh->SetIndexBuffer(ibo);
	mesh->SetPrimitiveType(PrimitiveType::Triangles);
	mesh->Compose();
	ModelComponent component;
	component.SetMesh(mesh);
	output->AddComponent(component);

	return true;
}