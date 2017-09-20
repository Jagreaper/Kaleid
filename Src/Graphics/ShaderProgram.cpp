#include "stdafx.hpp"
#include "ShaderProgram.hpp"
#include "Shader.hpp"
#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>

using namespace Kaleid::Graphics;
using namespace Kaleid::Math;

ShaderProgram::ShaderProgram()
{
	this->_id = glCreateProgram();
	if (this->_id == 0)
		throw std::runtime_error("glCreateProgram failed");
}

void ShaderProgram::Attach(Shader** shaders, unsigned int count)
{
	for (unsigned int index = 0; index < count; index++)
		glAttachShader(this->_id, shaders[index]->GetId());
}

void ShaderProgram::Attach(const std::vector<Shader*>& shaders)
{
	for (unsigned int index = 0; index < shaders.size(); index++)
		glAttachShader(this->_id, shaders[index]->GetId());
}

void ShaderProgram::Dettach(Shader** shaders, unsigned int count)
{
	for (unsigned int index = 0; index < count; index++)
		glDetachShader(this->_id, shaders[index]->GetId());
}

void ShaderProgram::Dettach(const std::vector<Shader*>& shaders)
{
	for (unsigned int index = 0; index < shaders.size(); index++)
		glDetachShader(this->_id, shaders[index]->GetId());
}

void ShaderProgram::Link()
{
	glLinkProgram(this->_id);
	this->Validate();
}

void ShaderProgram::Validate()
{
	GLint status;
	glGetProgramiv(this->_id, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::string msg("shader linking failure: ");

		GLint infoLogLength;
		glGetProgramiv(this->_id, GL_INFO_LOG_LENGTH, &infoLogLength);

		char* strInfoLog = new char[infoLogLength + 1];
		glGetProgramInfoLog(this->_id, infoLogLength, NULL, strInfoLog);

		msg += strInfoLog;
		delete[] strInfoLog;

		this->Dispose();
		throw std::runtime_error(msg);
	}
}

void ShaderProgram::Dispose()
{
	if (this->_id != 0)
	{
		glDeleteProgram(this->_id);
		this->_id = 0;
	}
}

const GLuint ShaderProgram::GetId() const
{
	return this->_id;
}

int ShaderProgram::GetUniformLocation(const char* name) const
{
	if (!name)
		throw std::runtime_error("name was NULL");

	int location = glGetUniformLocation(this->_id, name);
	if (location == -1)
		throw std::runtime_error(std::string("shader uniform not found: ") + name);

	return location;
}

int ShaderProgram::GetAttribLocation(const char* name) const
{
	if (!name)
		throw std::runtime_error("name was NULL");

	int location = glGetAttribLocation(this->_id, name);
	if (location == -1)
		throw std::runtime_error(std::string("shader attribute not found: ") + name);

	return location;
}

bool ShaderProgram::InUse() const
{
	int current_program = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &current_program);
	return (current_program == (GLint)this->_id);
}

#define PROGRAM_ATTRIB_N_UNIFORM_SETTERS(TYPE, TYPE_PREFIX, TYPE_SUFFIX) \
\
void ShaderProgram::SetAttrib(const char* name, TYPE v0) \
    { assert(this->InUse()); glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX (this->GetAttribLocation(name), v0); } \
void ShaderProgram::SetAttrib(const char* name, TYPE v0, TYPE v1) \
    { assert(this->InUse()); glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX (this->GetAttribLocation(name), v0, v1); } \
void ShaderProgram::SetAttrib(const char* name, TYPE v0, TYPE v1, TYPE v2) \
    { assert(this->InUse()); glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX (this->GetAttribLocation(name), v0, v1, v2); } \
void ShaderProgram::SetAttrib(const char* name, TYPE v0, TYPE v1, TYPE v2, TYPE v3) \
    { assert(this->InUse()); glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX (this->GetAttribLocation(name), v0, v1, v2, v3); } \
\
void ShaderProgram::SetAttrib1v(const char* name, const TYPE* v) \
    { assert(this->InUse()); glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX ## v (this->GetAttribLocation(name), v); } \
void ShaderProgram::SetAttrib2v(const char* name, const TYPE* v) \
    { assert(this->InUse()); glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX ## v (this->GetAttribLocation(name), v); } \
void ShaderProgram::SetAttrib3v(const char* name, const TYPE* v) \
    { assert(this->InUse()); glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX ## v (this->GetAttribLocation(name), v); } \
void ShaderProgram::SetAttrib4v(const char* name, const TYPE* v) \
    { assert(this->InUse()); glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX ## v (this->GetAttribLocation(name), v); } \
\
void ShaderProgram::SetUniform(const char* name, TYPE v0) \
    { assert(this->InUse()); glUniform1 ## TYPE_SUFFIX (this->GetUniformLocation(name), v0); } \
void ShaderProgram::SetUniform(const char* name, TYPE v0, TYPE v1) \
    { assert(this->InUse()); glUniform2 ## TYPE_SUFFIX (this->GetUniformLocation(name), v0, v1); } \
void ShaderProgram::SetUniform(const char* name, TYPE v0, TYPE v1, TYPE v2) \
    { assert(this->InUse()); glUniform3 ## TYPE_SUFFIX (this->GetUniformLocation(name), v0, v1, v2); } \
void ShaderProgram::SetUniform(const char* name, TYPE v0, TYPE v1, TYPE v2, TYPE v3) \
    { assert(this->InUse()); glUniform4 ## TYPE_SUFFIX (this->GetUniformLocation(name), v0, v1, v2, v3); } \
\
void ShaderProgram::SetUniform1v(const char* name, const TYPE* v, int count) \
    { assert(this->InUse()); glUniform1 ## TYPE_SUFFIX ## v (this->GetUniformLocation(name), count, v); } \
void ShaderProgram::SetUniform2v(const char* name, const TYPE* v, int count) \
    { assert(this->InUse()); glUniform2 ## TYPE_SUFFIX ## v (this->GetUniformLocation(name), count, v); } \
void ShaderProgram::SetUniform3v(const char* name, const TYPE* v, int count) \
    { assert(this->InUse()); glUniform3 ## TYPE_SUFFIX ## v (this->GetUniformLocation(name), count, v); } \
void ShaderProgram::SetUniform4v(const char* name, const TYPE* v, int count) \
    { assert(this->InUse()); glUniform4 ## TYPE_SUFFIX ## v (this->GetUniformLocation(name), count, v); } \

PROGRAM_ATTRIB_N_UNIFORM_SETTERS(float, , f);
PROGRAM_ATTRIB_N_UNIFORM_SETTERS(double, , d);
PROGRAM_ATTRIB_N_UNIFORM_SETTERS(int, I, i);
PROGRAM_ATTRIB_N_UNIFORM_SETTERS(unsigned int, I, ui);
#undef PROGRAM_ATTRIB_N_UNIFORM_SETTERS

void ShaderProgram::SetUniformMatrix2(const char* name, const float* v, int count, bool transpose)
{
	assert(this->InUse());
	glUniformMatrix2fv(this->GetUniformLocation(name), count, transpose, v);
}

void ShaderProgram::SetUniformMatrix3(const char* name, const float* v, int count, bool transpose)
{
	assert(this->InUse());
	glUniformMatrix3fv(this->GetUniformLocation(name), count, transpose, v);
}

void ShaderProgram::SetUniformMatrix4(const char* name, const float* v, int count, bool transpose)
{
	assert(this->InUse());
	glUniformMatrix4fv(this->GetUniformLocation(name), count, transpose, v);
}

void ShaderProgram::SetUniform(const char* name, const Matrix2F& m, bool transpose)
{
	assert(this->InUse());
	glUniformMatrix2fv(this->GetUniformLocation(name), 1, transpose, glm::value_ptr(m));
}

void ShaderProgram::SetUniform(const char* name, const Matrix3F& m, bool transpose)
{
	assert(this->InUse());
	glUniformMatrix3fv(this->GetUniformLocation(name), 1, transpose, glm::value_ptr(m));
}

void ShaderProgram::SetUniform(const char* name, const Matrix4F& m, bool transpose)
{
	assert(this->InUse());
	glUniformMatrix4fv(this->GetUniformLocation(name), 1, transpose, glm::value_ptr(m));
}

void ShaderProgram::SetUniform(const char* name, const Vector2F& v)
{
	this->SetUniform2v(name, glm::value_ptr(v));
}

void ShaderProgram::SetUniform(const char* name, const Vector3F& v)
{
	this->SetUniform3v(name, glm::value_ptr(v));
}

void ShaderProgram::SetUniform(const char* name, const Vector4F& v)
{
	this->SetUniform4v(name, glm::value_ptr(v));
}

void ShaderProgram::Bind()
{
	glUseProgram(this->_id);
}