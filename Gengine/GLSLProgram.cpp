#include "GLSLProgram.h"
#include "Error.h"

#include<fstream>
namespace Gengine {
	GLSLProgram::GLSLProgram() : _programID(0), _vertexShaderID(0), _fragmentShaderID(0), _numAtributes(0)
	{

	}


	GLSLProgram::~GLSLProgram()
	{
	}

	void GLSLProgram::compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath)
	{
		_programID = glCreateProgram();
		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (_vertexShaderID == 0)
		{
			fatalError("Vertex shader failed to complie");
		}

		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragmentShaderID == 0)
		{
			fatalError("Fragment shader failed to complie");
		}
		compileShader(vertexShaderFilePath, _vertexShaderID);
		compileShader(fragmentShaderFilePath, _fragmentShaderID);


	}
	void GLSLProgram::linkShaders()
	{

		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		glLinkProgram(_programID);

		GLuint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			glDeleteProgram(_programID);
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);

			fatalError("Shader failed to link");
		}
		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
	}
	void GLSLProgram::compileShader(const std::string &filePath, GLuint id)
	{
		std::ifstream vertexFile(filePath);
		if (vertexFile.fail())
		{
			perror(filePath.c_str());
			fatalError("Failed to open " + filePath);
		}
		std::string fileContents = "";
		std::string line;

		while (std::getline(vertexFile, line))
		{
			fileContents += line + "\n";
		}

		vertexFile.close();
		const char* contentsPtr = fileContents.c_str();
		glShaderSource(id, 1, &contentsPtr, nullptr);
		glCompileShader(id);

		GLint sucess = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &sucess);
		if (sucess == GL_FALSE)
		{
			perror(filePath.c_str());
			fatalError("Problem with shader - compile status");
		}
	}
	void GLSLProgram::addAttribute(const std::string &attributeName)
	{
		glBindAttribLocation(_programID, _numAtributes, attributeName.c_str());
		_numAtributes++;
	}
	void GLSLProgram::use()
	{
		glUseProgram(_programID);
		for (int i = 0; i < _numAtributes; i++)
		{
			glEnableVertexAttribArray(i);
		}
	}
	void GLSLProgram::unUse()
	{
		glUseProgram(0);
		for (int i = 0; i < _numAtributes; i++)
		{
			glDisableVertexAttribArray(i);
		}
	}
	GLint GLSLProgram::getUniformLocation(const std::string &uniformName)
	{
		GLint location = glGetUniformLocation(_programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX)
		{
			fatalError("Uniform error : " + uniformName + " not found in shader");
		}
		return location;
	}
}