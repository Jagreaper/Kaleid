#pragma once

#include "stdafx.hpp"
#include "Shader.hpp"
#include <vector>

namespace Kaleid::Graphics
{
	class ShaderProgram
	{
	public:
#ifdef KALEID_GRAPHICS_DLL
		ShaderProgram();
		ShaderProgram(const std::vector<Shader*>& shaders);
		ShaderProgram(Shader** shaders, unsigned int count);
		~ShaderProgram();
#endif
		void KALEID_GRAPHICS_API Attach(Shader** shaders, unsigned int count);
		void KALEID_GRAPHICS_API Attach(const std::vector<Shader*>& shaders);
		void KALEID_GRAPHICS_API Dettach(Shader** shaders, unsigned int count);
		void KALEID_GRAPHICS_API Dettach(const std::vector<Shader*>& shaders);
		void KALEID_GRAPHICS_API Link();
		void KALEID_GRAPHICS_API Dispose();
		const unsigned int KALEID_GRAPHICS_API GetId() const;
		bool KALEID_GRAPHICS_API InUse() const;
		int KALEID_GRAPHICS_API GetUniformLocation(const char* name) const;
		int KALEID_GRAPHICS_API GetAttribLocation(const char* name) const;

#define _TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(OGL_TYPE) \
		void KALEID_GRAPHICS_API SetAttrib(const char* name, OGL_TYPE v0); \
		void KALEID_GRAPHICS_API SetAttrib(const char* name, OGL_TYPE v0, OGL_TYPE v1); \
		void KALEID_GRAPHICS_API SetAttrib(const char* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2); \
		void KALEID_GRAPHICS_API SetAttrib(const char* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3); \
\
		void KALEID_GRAPHICS_API SetAttrib1v(const char* name, const OGL_TYPE* v); \
		void KALEID_GRAPHICS_API SetAttrib2v(const char* name, const OGL_TYPE* v); \
		void KALEID_GRAPHICS_API SetAttrib3v(const char* name, const OGL_TYPE* v); \
		void KALEID_GRAPHICS_API SetAttrib4v(const char* name, const OGL_TYPE* v); \
\
		void KALEID_GRAPHICS_API SetUniform(const char* name, OGL_TYPE v0); \
		void KALEID_GRAPHICS_API SetUniform(const char* name, OGL_TYPE v0, OGL_TYPE v1); \
		void KALEID_GRAPHICS_API SetUniform(const char* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2); \
		void KALEID_GRAPHICS_API SetUniform(const char* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3); \
\
		void KALEID_GRAPHICS_API SetUniform1v(const char* name, const OGL_TYPE* v, int count=1); \
		void KALEID_GRAPHICS_API SetUniform2v(const char* name, const OGL_TYPE* v, int count=1); \
		void KALEID_GRAPHICS_API SetUniform3v(const char* name, const OGL_TYPE* v, int count=1); \
		void KALEID_GRAPHICS_API SetUniform4v(const char* name, const OGL_TYPE* v, int count=1); \

		_TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(float)
		_TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(double)
		_TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(int)
		_TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(unsigned int)

		void KALEID_GRAPHICS_API SetUniformMatrix2(const char* name, const float* v, int count = 1, bool transpose = false);
		void KALEID_GRAPHICS_API SetUniformMatrix3(const char* name, const float* v, int count = 1, bool transpose = false);
		void KALEID_GRAPHICS_API SetUniformMatrix4(const char* name, const float* v, int count = 1, bool transpose = false);
		void KALEID_GRAPHICS_API SetUniform(const char* name, const glm::mat2& m, bool transpose = false);
		void KALEID_GRAPHICS_API SetUniform(const char* name, const glm::mat3& m, bool transpose = false);
		void KALEID_GRAPHICS_API SetUniform(const char* name, const glm::mat4& m, bool transpose = false);
		void KALEID_GRAPHICS_API SetUniform(const char* name, const glm::vec2& v);
		void KALEID_GRAPHICS_API SetUniform(const char* name, const glm::vec3& v);
		void KALEID_GRAPHICS_API SetUniform(const char* name, const glm::vec4& v);
#ifdef KALEID_GRAPHICS_DLL
	private:
		void Validate();
		unsigned int _id;
#endif
	};
}