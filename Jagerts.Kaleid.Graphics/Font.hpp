#pragma once

#include "Jagerts.Kaleid.Shared/Common.hpp"
#include "Jagerts.Kaleid.Math/OrthographicCamera.hpp"
#include <vector>
#include <string>

namespace Jagerts::Kaleid::Graphics
{
	class Texture;
	class ShaderProgram;
	class Mesh;

	class JAGERTS_KALEID_GRAPHICS_API Font
	{
	public:
		Font(const char* font);
	private:
		static ShaderProgram* _shader_program;
		static Mesh* _mesh;
		static Texture* _texture;
		static Jagerts::Kaleid::Math::OrthographicCamera _camera;
		static void* _library;
	    void* _face = NULL;

		friend class Renderer;
	};
}