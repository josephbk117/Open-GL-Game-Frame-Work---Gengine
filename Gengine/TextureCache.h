#pragma once
#include<map>
#include<string>
#include "GLTexture.h"
namespace Gengine {
	class TextureCache
	{
	private:
		std::map<std::string, GLTexture> _textureMap;

	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(std::string);

	};
}

