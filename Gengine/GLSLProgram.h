#pragma once
#include<string>
#include<GL\glew.h>
namespace Gengine {
	class GLSLProgram
	{
	private:
		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
		int _numAtributes;

		void compileShader(const std::string &filePath, GLuint id);
	public:
		GLSLProgram();
		~GLSLProgram();
		void compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);
		void linkShaders();
		void addAttribute(const std::string &attributeName);
		void use();
		void unUse();
		GLint getUniformLocation(const std::string &uniformName);
	};
}

