// TextureLoader.cpp

#include "TextureLoader.h"

// Load texture from file
bool TextureLoader::LoadTexture(const std::string& filename, Textures::TextureType type)
{
	bool loaded = false;
	std::unique_ptr<sf::Texture> texture(new sf::Texture);
	
	loaded = texture->loadFromFile(filename);
	if (loaded){
		m_textures[type] = std::move(texture);
	}
    else{
        exit(-2);
    }

	return loaded;
}

// Get a pointer to the loaded texture if it is loaded. Will return nullptr if texture was not loaded.
sf::Texture* TextureLoader::GetTextureRef(Textures::TextureType type)
{
	auto found = m_textures.find(type);

	if (found != m_textures.end()){
		return found->second.get();
	}

	return nullptr;
}