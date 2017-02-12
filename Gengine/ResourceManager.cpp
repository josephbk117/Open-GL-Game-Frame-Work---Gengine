#include "ResourceManager.h"
#include "TextureCache.h"
#include <string>
namespace Gengine {
	TextureCache ResourceManager::_textureCache;

	GLTexture ResourceManager::getTexture(std::string texturePath)
	{
		return _textureCache.getTexture(texturePath);
	}
}