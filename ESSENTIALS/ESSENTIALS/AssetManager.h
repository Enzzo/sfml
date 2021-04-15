#pragma once
#include <string>
#include <map>

#include <SFML/Graphics.hpp>
class AssetManager{
	
	static AssetManager* instance;

	std::map<std::string, sf::Texture> m_texture;

public:
	AssetManager();
	static sf::Texture& GetTexture(const std::string&);
};

