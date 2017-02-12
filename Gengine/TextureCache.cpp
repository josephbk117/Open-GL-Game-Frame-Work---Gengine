#include "TextureCache.h"
#include "GLTexture.h"
#include "ImageLoader.h"
#include <string>
#include <map>
#include <iostream>

namespace Gengine {

	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath)
	{
		//std::map<std::string,GLTexture>::iterator mit =_textureMap.find(texturePath); //mit - map iterator
		//Instead of typing long thing use auto --like var in C#
		auto mit = _textureMap.find(texturePath);//look up the texture and see if its in the map
		if (mit == _textureMap.end())
		{
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);
			std::pair<std::string, GLTexture> newPair(texturePath, newTexture); //Can also use make_pair and pass in args

			_textureMap.insert(newPair);
			std::cout << "Texture cached - loaded\n";
			return newTexture;
		}
		std::cout << "Texture cached - pre-loaded\n";
		return mit->second;
	}
}