#include "SpriteBatch.h"

namespace Gengine {

	SpriteBatch::SpriteBatch():_vbo(0),_vao(0)
	{
	}


	SpriteBatch::~SpriteBatch()
	{
	}
	void SpriteBatch::init() {}
	void SpriteBatch::begin() {}
	void SpriteBatch::end() {}
	void SpriteBatch::draw(const glm::vec4 &destRect, const glm::uvec4 &uvRect, GLuint texture, float depth,const Colour &color)//pass by ref faster and const prevents it from being changed
	{
		Glyph* newGlyph = new Glyph;
		newGlyph->depth = depth;
		newGlyph->texture = texture;

		newGlyph->topLeft.color = color;
		newGlyph->topLeft.setPosition(destRect.x, destRect.y + uvRect.w); //can use uvRect[3] instead of w
		newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		newGlyph->bottomLeft.color = color;
		newGlyph->bottomLeft.setPosition(destRect.x, destRect.y); 
		newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);

		newGlyph->bottomRight.color = color;
		newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		newGlyph->bottomRight.setUV(uvRect.x +uvRect.z, uvRect.y );
		
		newGlyph->topRight.color = color;
		newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + uvRect.w);
		newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		_glyphs.push_back(newGlyph);
	}
	void SpriteBatch::renderBatch() {}
	void SpriteBatch::createVertexArray()
	{
		if(_vao == 0)
			glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);
		if(_vbo == 0)
			glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	}
}