#include "stdafx.hpp"
#include "Renderer.hpp"

using namespace Kaleid::Graphics;

Renderer::Renderer()
{

}

void Renderer::Load()
{

}

void Renderer::Dispose()
{

}

void Renderer::Clear(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}