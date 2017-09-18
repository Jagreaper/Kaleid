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
		KALEID_GRAPHICS_API void Dispose();
		KALEID_GRAPHICS_API const unsigned int GetId() const;
		KALEID_GRAPHICS_API bool InUse() const;
		KALEID_GRAPHICS_API int GetUniformLocation(const char* name) const;
		KALEID_GRAPHICS_API int GetAttribLocation(const char* name) const;

#define _PROGRAM_ATTRIB_N_UNIFORM_SETTERS(OGL_TYPE) \
		KALEID_GRAPHICS_API void SetAttrib(const char* name, OGL_TYPE v0); \
		KALEID_GRAPHICS_API void SetAttrib(const char* name, OGL_TYPE v0, OGL_TYPE v1); \
		KALEID_GRAPHICS_API void SetAttrib(const char* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2); \
		KALEID_GRAPHICS_API void SetAttrib(const char* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3); \
\
		KALEID_GRAPHICS_API void SetAttrib1v(const char* name, const OGL_TYPE* v); \
		KALEID_GRAPHICS_API void SetAttrib2v(const char* name, const OGL_TYPE* v); \
		KALEID_GRAPHICS_API void SetAttrib3v(const char* name, const OGL_TYPE* v); \
		KALEID_GRAPHICS_API void SetAttrib4v(const char* name, const OGL_TYPE* v); \
\
		KALEID_GRAPHICS_API void SetUniform(const char* name, OGL_TYPE v0); \
		KALEID_GRAPHICS_API void SetUniform(const char* name, OGL_TYPE v0, OGL_TYPE v1); \
		KALEID_GRAPHICS_API void SetUniform(const char* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2); \
		KALEID_GRAPHICS_API void SetUniform(const char* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3); \
\
		KALEID_GRAPHICS_API void SetUniform1v(const char* name, const OGL_TYPE* v, int count=1); \
		KALEID_GRAPHICS_API void SetUniform2v(const char* name, const OGL_TYPE* v, int count=1); \
		KALEID_GRAPHICS_API void SetUniform3v(const char* name, const OGL_TYPE* v, int count=1); \
		KALEID_GRAPHICS_API void SetUniform4v(const char* name, const OGL_TYPE* v, int count=1); \

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
		ShaderProgram();
		ShaderProgram(const std::vector<Shader*>& shaders);
		ShaderProgram(Shader** shaders, unsigned int count);
		~ShaderProgram();

	private:
		void Validate();
		unsigned int _id;
#endif
	};
}
API_END