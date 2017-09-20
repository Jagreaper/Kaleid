#include "stdafx.hpp"
#include "Shape.hpp"

using namespace Kaleid::Geometry;

void Shape::SetFaces(std::vector<Face>& faces)
{
	this->_faces = faces;
}

std::vector<Face>& Shape::GetFaces()
{
	return this->_faces;
}

std::vector<Face> Shape::GetFaces() const
{
	return this->_faces;
}