#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class AssetManager {
public:
	AssetManager();
	static sf::Texture& GetTexture(std::string const& filename);

private:
	std::map<std::string, sf::Texture> m_textures;

	//AssetManager is a singleton, so only one instance can exist at a time
	//sInstance holds a static pointer to the single manager instance

	//Статический указатель на себя. Может быть только один
	static AssetManager* sInstance;
};