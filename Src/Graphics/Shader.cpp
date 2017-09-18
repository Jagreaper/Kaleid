#include "stdafx.hpp"
#include "Shader.hpp"
#include <stdexcept>

using namespace Kaleid::Graphics;

Shader::Shader(const ShaderType type)
{
	this->_id = glCreateShader(type);
	if (this->_id == 0)
		throw std::runtime_error("glCreateShader failed");
}

void Shader::SetSource(const char** source)
{
	glShaderSource(this->_id, 1, source, NULL);
}

void Shader::Compile()
{
	glCompileShader(this->_id);
	this->Validate();
}

void Shader::Validate()
{
	GLint status;
	glGetShaderiv(this->_id, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		std::string msg("Compile failure in shader fragment:\n");

		GLint infoLogLength;
		glGetShaderiv(this->_id, GL_INFO_LOG_LENGTH, &infoLogLength);

		char* strInfoLog = new char[infoLogLength + 1];
		glGetShaderInfoLog(this->_id, infoLogLength, NULL, strInfoLog);

		msg += strInfoLog;
		delete[] strInfoLog;

		this->Dispose();
		throw std::runtime_error(msg);
	}
}

void Shader::Dispose()
{
	if (this->_id != 0)
	{
		glDeleteShader(this->_id);
		this->_id = 0;
	}
}

const unsigned int Shader::GetId() const
{
	return this->_id;
}