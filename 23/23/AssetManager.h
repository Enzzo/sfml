#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class AssetManager{
public:
	AssetManager();
	static sf::Texture SetTexture(const std::string& path);
private:
	static AssetManager* instance;
	std::map<std::string, sf::Texture> textures;
};

class FailedTexture {
public:
	FailedTexture(const std::string& s);
	std::string What()const;
private:
	std::string what;
};