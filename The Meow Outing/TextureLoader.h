// TextureLoader.h
// Resposible for loading textures from files and providing pointers to the textures to those classes that need them.

#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Global_Enums.h"

class TextureLoader
{
public:
	// Loads the given texture from file into memory. It is important that this is called before attempting to get a texture
	bool LoadTexture(const std::string& filename, Textures::TextureType type);

	// Get a pointer to the loaded texture if it is loaded. Will return nullptr if texture was not loaded.
	sf::Texture* GetTextureRef(Textures::TextureType type);

private:
	std::map<Textures::TextureType, std::unique_ptr<sf::Texture>> m_textures;
};

#endif