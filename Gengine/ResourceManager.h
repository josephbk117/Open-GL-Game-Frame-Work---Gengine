#pragma once
#include "TextureCache.h"
#include <string>
namespace Gengine {
	class ResourceManager
	{

	private:
		static TextureCache _textureCache;
	public:
		static GLTexture getTexture(std::string texturePath);
		static GLuint boundTexture;
	};
}

