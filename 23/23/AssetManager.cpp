#include "AssetManager.h"
#include <exception>
#include <iostream>

FailedTexture::FailedTexture(const std::string& s) {
	what = s;
};
std::string FailedTexture::What()const {
	return what;
};

AssetManager::AssetManager() {
	if (instance == nullptr)
		instance = this;
	else
		throw std::exception("you cannot create another instance of this class");
};

sf::Texture AssetManager::SetTexture(const std::string& path){
	std::map<std::string, sf::Texture>::iterator tex = instance->textures.find(path);
	if(tex == instance->textures.end())
		if (!instance->textures[path].loadFromFile(path)) {
			throw FailedTexture("Fsdf");
		}
		
	return instance->textures.at(path);
}

AssetManager* AssetManager::instance = nullptr;