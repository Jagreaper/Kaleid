#include "Jagerts.Kaleid.Game\RenderableShape.hpp"

using namespace Jagerts::Kaleid::Graphics;
using namespace Jagerts::Kaleid::Game;

void RenderableShape::Render(Renderer*& renderer, std::function<void(ShaderProgram*&)> arguments)
{
	renderer->RenderMesh(this->_mesh, this->_shader_program, NULL, arguments);
}

void RenderableShape::SetShaderProgram(ShaderProgram*& shader_program)
{
	this->_shader_program = shader_program;
}

ShaderProgram* RenderableShape::GetShaderProgram()
{
	return this->_shader_program;
}