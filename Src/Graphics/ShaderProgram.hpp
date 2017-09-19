#pragma once

#include "stdafx.hpp"
#include "Shader.hpp"
#include <vector>

API_BEGIN
namespace Kaleid::Graphics
{
	class GraphicsFactory;
	class Mesh;

	class KALEID_GRAPHICS_API ShaderProgram sealed
	{
	public:
		void Attach(Shader** shaders, unsigned int count);
		void Attach(const std::vector<Shader*>& shaders);
		void Dettach(Shader** shaders, unsigned int count);
		void Dettach(const std::vector<Shader*>& shaders);
		void Link();
		bool InUse() const;
		int GetUniformLocation(const char* name) const;
		int GetAttribLocation(const char* name) const;

#define _PROGRAM_ATTRIB_N_UNIFORM_SETTERS(TYPE) \
		void SetAttrib(const char* name, TYPE v0); \
		void SetAttrib(const char* name, TYPE v0, TYPE v1); \
		void SetAttrib(const char* name, TYPE v0, TYPE v1, TYPE v2); \
		void SetAttrib(const char* name, TYPE v0, TYPE v1, TYPE v2, TYPE v3); \
\
		void SetAttrib1v(const char* name, const TYPE* v); \
		void SetAttrib2v(const char* name, const TYPE* v); \
		void SetAttrib3v(const char* name, const TYPE* v); \
		void SetAttrib4v(const char* name, const TYPE* v); \
\
		void SetUniform(const char* name, TYPE v0); \
		void SetUniform(const char* name, TYPE v0, TYPE v1); \
		void SetUniform(const char* name, TYPE v0, TYPE v1, TYPE v2); \
		void SetUniform(const char* name, TYPE v0, TYPE v1, TYPE v2, TYPE v3); \
\
		void SetUniform1v(const char* name, const TYPE* v, int count = 1); \
		void SetUniform2v(const char* name, const TYPE* v, int count = 1); \
		void SetUniform3v(const char* name, const TYPE* v, int count = 1); \
		void SetUniform4v(const char* name, const TYPE* v, int count = 1); \

		_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(float)
		_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(double)
		_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(int)
		_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(unsigned int)
#undef _PROGRAM_ATTRIB_N_UNIFORM_SETTERS

		void SetUniformMatrix2(const char* name, const float* v, int count = 1, bool transpose = false);
		void SetUniformMatrix3(const char* name, const float* v, int count = 1, bool transpose = false);
		void SetUniformMatrix4(const char* name, const float* v, int count = 1, bool transpose = false);
		void SetUniform(const char* name, const glm::mat2& m, bool transpose = false);
		void SetUniform(const char* name, const glm::mat3& m, bool transpose = false);
		void SetUniform(const char* name, const glm::mat4& m, bool transpose = false);
		void SetUniform(const char* name, const glm::vec2& v);
		void SetUniform(const char* name, const glm::vec3& v);
		void SetUniform(const char* name, const glm::vec4& v);
	private:
		ShaderProgram();
		void Dispose();
		void Bind();
		void Validate();
		const unsigned int GetId() const;

		unsigned int _id;

		friend class GraphicsFactory;
		friend class Mesh;
	};
}
API_END