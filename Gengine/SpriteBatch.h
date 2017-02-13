#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Vertex.h"
#include<vector>
namespace Gengine {

	struct Glyph
	{
		GLuint texture;
		float depth;
		Vertex topLeft, topRight, bottomLeft, bottomRight;
	};

	class SpriteBatch
	{
	private:
		GLuint _vbo;
		GLuint _vao;
		std::vector<Glyph*> _glyphs;
		void createVertexArray();


	public:
		SpriteBatch();
		~SpriteBatch();
		void init();
		void begin();
		void end();
		void draw(const glm::vec4 &destRect,const glm::uvec4 &uvRect,GLuint texture,float depth,const Colour &color); //pass by ref faster and const prevents it from being changed
		void renderBatch();
	};

}