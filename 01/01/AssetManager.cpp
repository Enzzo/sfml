#include "AssetManager.h"
#include <iostream>
#include <assert.h>

AssetManager* AssetManager::sInstance = nullptr;

AssetManager::AssetManager() {
	//Only allow one Asset Manager to exist
	//Otherwise throw an exception
	assert(sInstance == nullptr);
	sInstance = this;
}

sf::Texture& AssetManager::GetTexture(std::string const& filename) {
	
	std::map<std::string, sf::Texture>& texMap = sInstance->m_textures;
	const std::map<std::string, sf::Texture>::iterator it = texMap.find(filename);

	if (it == texMap.end()) {
		sf::Texture& texture = texMap[filename];
		texture.loadFromFile(filename);
		return texture;
	}

	return it->second;
}