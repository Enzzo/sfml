#pragma once
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <assert.h>
#include <iostream>

class AssetManager{
public:
	AssetManager();
	static AssetManager* instance;

	static sf::Texture& GetTexture(const std::string&);

private:
	std::map<std::string, sf::Texture> mapTex;
};

