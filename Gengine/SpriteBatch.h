#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Vertex.h"
#include<vector>
namespace Gengine {

	enum class GlyphSortType {
		NONE, FRONT_TO_BACK,BACK_TO_FRONT,TEXTURE
	};

	struct Glyph
	{
		GLuint texture;
		float depth;
		Vertex topLeft, topRight, bottomLeft, bottomRight;
	};


	class RenderBatch 
	{
		public:
			RenderBatch(GLuint offset, GLuint numOfVertices, GLuint texture):offset(offset),numOfVertices(numOfVertices)
				,texture(texture)
			{

			}

			GLuint offset;
			GLuint numOfVertices;
			GLuint texture;
	};

	class SpriteBatch
	{
	private:
		GLuint _vbo;
		GLuint _vao;
		std::vector<Glyph*> _glyphs;
		std::vector<RenderBatch> _renderBatches;

		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph *a,Glyph *b);
		static bool comapreBackToFront(Glyph *a, Glyph *b); 
		static bool compareTexture(Glyph *a, Glyph *b);
		GlyphSortType _sortType;


	public:
		SpriteBatch();
		~SpriteBatch();
		void init();
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();
		void draw(const glm::vec4 &destRect,const glm::uvec4 &uvRect,GLuint texture,float depth,const Colour &color); //pass by ref faster and const prevents it from being changed
		void renderBatch();
	};

}