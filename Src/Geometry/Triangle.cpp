#include "stdafx.hpp"
#include "Triangle.hpp"

using namespace Kaleid::Geometry;

Triangle::Triangle()
{
	this->_verticies.push_back(VertexF());
	this->_verticies.push_back(VertexF());
	this->_verticies.push_back(VertexF());
}

Triangle::Triangle(VertexF& v1, VertexF& v2, VertexF& v3)
	: Triangle()
{
	this->_verticies[0] = v1;
	this->_verticies[1] = v2;
	this->_verticies[2] = v3;
}

void Triangle::SetP1(VertexF& ver)
{
	this->_verticies[0] = ver;
}

void Triangle::SetP2(VertexF& ver)
{
	this->_verticies[1] = ver;
}

void Triangle::SetP3(VertexF& ver)
{
	this->_verticies[2] = ver;
}

VertexF& Triangle::GetP1()
{
	return this->_verticies[0];
}

VertexF Triangle::GetP1() const
{
	return this->_verticies[0];
}

VertexF& Triangle::GetP2()
{
	return this->_verticies[1];
}

VertexF Triangle::GetP2() const
{
	return this->_verticies[1];
}

VertexF& Triangle::GetP3()
{
	return this->_verticies[2];
}

VertexF Triangle::GetP3() const
{
	return this->_verticies[2];
}