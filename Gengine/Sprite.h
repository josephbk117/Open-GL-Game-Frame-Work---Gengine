#pragma once
#include <GL\glew.h>
#include "GLTexture.h"
#include <string>
namespace Gengine {
	class Sprite
	{

	private:
		int _x, _y;
		int _width, _height;
		GLuint _vboID;
		GLTexture _texture;
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float width, float height, std::string texturePath);
		void draw();
	};
}

