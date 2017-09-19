#include "stdafx.hpp"
#include "Model.hpp"
#include "VectorHelper.hpp"

using namespace Kaleid::Game;
using namespace Kaleid::Graphics;
using namespace Kaleid::Helpers;

Mesh* Model::MeshAt(int index)
{
	return this->_meshes[index];
}

void Model::AddMesh(Mesh* meshes)
{
	this->_meshes.push_back(meshes);
}

void Model::AddMeshes(std::vector<Mesh*>* meshes)
{
	VectorHelper::AddRange(&this->_meshes, meshes);
}

void Model::RemoveMesh(int index)
{
	this->_meshes.erase(this->_meshes.begin() + index);
}

void Model::RemoveMesh(Mesh* mesh)
{
	VectorHelper::RemoveItem(&this->_meshes, mesh);
}

void Model::SetMeshes(std::vector<Mesh*>& meshes)
{
	this->_meshes = meshes;
}

std::vector<Mesh*>* Model::GetMeshes()
{
	return &this->_meshes;
}
