#pragma once

#include "stdafx.hpp"
#include "Shader.hpp"
#include <vector>

namespace polarious::graphics
{
	class shader_program
	{
	public:
		shader_program(const std::vector<shader_fragment>& shaders);
		shader_program(shader_fragment* fragments, unsigned int count);
		~shader_program();
		void dispose();
		const GLuint get_id() const;
		bool in_use() const;
		int get_uniform_location(const char* name) const;
		int get_attrib_location(const char* name) const;

#define _TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(OGL_TYPE) \
		void set_attrib(const char* name, OGL_TYPE v0); \
		void set_attrib(const char* name, OGL_TYPE v0, OGL_TYPE v1); \
		void set_attrib(const char* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2); \
		void set_attrib(const char* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3); \
\
		void set_attrib1v(const char* name, const OGL_TYPE* v); \
		void set_attrib2v(const char* name, const OGL_TYPE* v); \
		void set_attrib3v(const char* name, const OGL_TYPE* v); \
		void set_attrib4v(const char* name, const OGL_TYPE* v); \
\
		void set_uniform(const char* name, OGL_TYPE v0); \
		void set_uniform(const char* name, OGL_TYPE v0, OGL_TYPE v1); \
		void set_uniform(const char* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2); \
		void set_uniform(const char* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3); \
\
		void set_uniform1v(const char* name, const OGL_TYPE* v, int count=1); \
		void set_uniform2v(const char* name, const OGL_TYPE* v, int count=1); \
		void set_uniform3v(const char* name, const OGL_TYPE* v, int count=1); \
		void set_uniform4v(const char* name, const OGL_TYPE* v, int count=1); \

		_TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(float)
			_TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(double)
			_TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(int)
			_TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(unsigned int)

			void set_uniform_matrix2(const char* name, const float* v, int count = 1, bool transpose = GL_FALSE);
		void set_uniform_matrix3(const char* name, const float* v, int count = 1, bool transpose = GL_FALSE);
		void set_uniform_matrix4(const char* name, const float* v, int count = 1, bool transpose = GL_FALSE);
		void set_uniform(const char* name, const glm::mat2& m, bool transpose = GL_FALSE);
		void set_uniform(const char* name, const glm::mat3& m, bool transpose = GL_FALSE);
		void set_uniform(const char* name, const glm::mat4& m, bool transpose = GL_FALSE);
		void set_uniform(const char* name, const glm::vec2& v);
		void set_uniform(const char* name, const glm::vec3& v);
		void set_uniform(const char* name, const glm::vec4& v);
	private:
		void validate();
		GLuint _id;
	};
}