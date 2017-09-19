#pragma once

#include "stdafx.hpp"
#include "Mesh.hpp"
#include <vector>

API_BEGIN
namespace Kaleid::Game
{
	class KALEID_GAME_API Model sealed
	{
	public:
		Kaleid::Graphics::Mesh* MeshAt(int index);
		void AddMesh(Kaleid::Graphics::Mesh* meshes);
		void AddMeshes(std::vector<Kaleid::Graphics::Mesh*>* meshes);
		void RemoveMesh(int index);
		void RemoveMesh(Kaleid::Graphics::Mesh* mesh);
		void SetMeshes(std::vector<Kaleid::Graphics::Mesh*>& meshes);
		std::vector<Kaleid::Graphics::Mesh*>* GetMeshes();
	private:
		std::vector<Kaleid::Graphics::Mesh*> _meshes;
	};
}
API_END