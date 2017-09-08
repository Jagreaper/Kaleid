#pragma once

#include "stdafx.hpp"
#include "Shader.hpp"
#include <vector>

namespace Kaleid::Graphics
{
	class ShaderProgram
	{
	public:
		ShaderProgram();
		ShaderProgram(const std::vector<Shader*>& shaders);
		ShaderProgram(Shader** shaders, unsigned int count);
		~ShaderProgram();
		void Attach(Shader** shaders, unsigned int count);
		void Attach(const std::vector<Shader*>& shaders);
		void Dettach(Shader** shaders, unsigned int count);
		void Dettach(const std::vector<Shader*>& shaders);
		void Link();
		void Dispose();
		const unsigned int GetId() const;
		bool InUse() const;
		int GetUniformLocation(const char* name) const;
		int GetAttribLocation(const char* name) const;

#define _TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(OGL_TYPE) \
		void SetAttrib(const char* name, OGL_TYPE v0); \
		void SetAttrib(const char* name, OGL_TYPE v0, OGL_TYPE v1); \
		void SetAttrib(const char* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2); \
		void SetAttrib(const char* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3); \
\
		void SetAttrib1v(const char* name, const OGL_TYPE* v); \
		void SetAttrib2v(const char* name, const OGL_TYPE* v); \
		void SetAttrib3v(const char* name, const OGL_TYPE* v); \
		void SetAttrib4v(const char* name, const OGL_TYPE* v); \
\
		void SetUniform(const char* name, OGL_TYPE v0); \
		void SetUniform(const char* name, OGL_TYPE v0, OGL_TYPE v1); \
		void SetUniform(const char* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2); \
		void SetUniform(const char* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3); \
\
		void SetUniform1v(const char* name, const OGL_TYPE* v, int count=1); \
		void SetUniform2v(const char* name, const OGL_TYPE* v, int count=1); \
		void SetUniform3v(const char* name, const OGL_TYPE* v, int count=1); \
		void SetUniform4v(const char* name, const OGL_TYPE* v, int count=1); \

		_TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(float)
		_TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(double)
		_TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(int)
		_TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(unsigned int)

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
		void Validate();
		unsigned int _id;
	};
}