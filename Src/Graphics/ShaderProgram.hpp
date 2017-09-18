#pragma once

#include "stdafx.hpp"
#include "Shader.hpp"
#include <vector>

API_BEGIN
namespace Kaleid::Graphics
{
	class ShaderProgram
	{
	public:
		KALEID_GRAPHICS_API void Attach(Shader** shaders, unsigned int count);
		KALEID_GRAPHICS_API void Attach(const std::vector<Shader*>& shaders);
		KALEID_GRAPHICS_API void Dettach(Shader** shaders, unsigned int count);
		KALEID_GRAPHICS_API void Dettach(const std::vector<Shader*>& shaders);
		KALEID_GRAPHICS_API void Link();
		KALEID_GRAPHICS_API bool InUse() const;
		KALEID_GRAPHICS_API int GetUniformLocation(const char* name) const;
		KALEID_GRAPHICS_API int GetAttribLocation(const char* name) const;

#define _PROGRAM_ATTRIB_N_UNIFORM_SETTERS(TYPE) \
		KALEID_GRAPHICS_API void SetAttrib(const char* name, TYPE v0); \
		KALEID_GRAPHICS_API void SetAttrib(const char* name, TYPE v0, TYPE v1); \
		KALEID_GRAPHICS_API void SetAttrib(const char* name, TYPE v0, TYPE v1, TYPE v2); \
		KALEID_GRAPHICS_API void SetAttrib(const char* name, TYPE v0, TYPE v1, TYPE v2, TYPE v3); \
\
		KALEID_GRAPHICS_API void SetAttrib1v(const char* name, const TYPE* v); \
		KALEID_GRAPHICS_API void SetAttrib2v(const char* name, const TYPE* v); \
		KALEID_GRAPHICS_API void SetAttrib3v(const char* name, const TYPE* v); \
		KALEID_GRAPHICS_API void SetAttrib4v(const char* name, const TYPE* v); \
\
		KALEID_GRAPHICS_API void SetUniform(const char* name, TYPE v0); \
		KALEID_GRAPHICS_API void SetUniform(const char* name, TYPE v0, TYPE v1); \
		KALEID_GRAPHICS_API void SetUniform(const char* name, TYPE v0, TYPE v1, TYPE v2); \
		KALEID_GRAPHICS_API void SetUniform(const char* name, TYPE v0, TYPE v1, TYPE v2, TYPE v3); \
\
		KALEID_GRAPHICS_API void SetUniform1v(const char* name, const TYPE* v, int count = 1); \
		KALEID_GRAPHICS_API void SetUniform2v(const char* name, const TYPE* v, int count = 1); \
		KALEID_GRAPHICS_API void SetUniform3v(const char* name, const TYPE* v, int count = 1); \
		KALEID_GRAPHICS_API void SetUniform4v(const char* name, const TYPE* v, int count = 1); \

		_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(float)
		_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(double)
		_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(int)
		_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(unsigned int)
#undef _PROGRAM_ATTRIB_N_UNIFORM_SETTERS

		KALEID_GRAPHICS_API void SetUniformMatrix2(const char* name, const float* v, int count = 1, bool transpose = false);
		KALEID_GRAPHICS_API void SetUniformMatrix3(const char* name, const float* v, int count = 1, bool transpose = false);
		KALEID_GRAPHICS_API void SetUniformMatrix4(const char* name, const float* v, int count = 1, bool transpose = false);
		KALEID_GRAPHICS_API void SetUniform(const char* name, const glm::mat2& m, bool transpose = false);
		KALEID_GRAPHICS_API void SetUniform(const char* name, const glm::mat3& m, bool transpose = false);
		KALEID_GRAPHICS_API void SetUniform(const char* name, const glm::mat4& m, bool transpose = false);
		KALEID_GRAPHICS_API void SetUniform(const char* name, const glm::vec2& v);
		KALEID_GRAPHICS_API void SetUniform(const char* name, const glm::vec3& v);
		KALEID_GRAPHICS_API void SetUniform(const char* name, const glm::vec4& v);
#ifdef KALEID_GRAPHICS_DLL
		void Dispose();
		ShaderProgram();

		void Bind();
		const unsigned int GetId() const;
	private:
		void Validate();
		unsigned int _id;
#endif
	};
}
API_END