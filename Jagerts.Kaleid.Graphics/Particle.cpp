#include "Particle.hpp"
#include "Jagerts.Kaleid.Graphics/Point.hpp"

using namespace Jagerts::Kaleid::Graphics;

jkGetterSetterSourceDefinition(Particle, ShaderProgram, ShaderProgram* const, this->_shader_program)

jkgRenderableObjectSource(Particle)
{
	Mesh* mesh = Point::GetMesh();
	renderer->RenderMesh(mesh, this->_shader_program, NULL, arguments);
}