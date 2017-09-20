#include "stdafx.hpp"
#include "Face.hpp"

using namespace Kaleid::Geometry;

void Face::SetVerticies(std::vector<Vertex>& verticies)
{
	this->_verticies = verticies;
}

std::vector<Vertex>& Face::GetVerticies()
{
	return this->_verticies;
}

std::vector<Vertex> Face::GetVerticies() const
{
	return this->_verticies;
}