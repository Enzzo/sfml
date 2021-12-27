#include <cassert>
#include <iostream>

#include "AssetManager.h"

void Alert(const std::string& s, const std::string& file, const int line) {
	std::cerr << file << "(" << line << ")" << std::endl;
	std::cerr << "Can't load [" << s << "]";
	abort();
}

#define ABORT_TEXTURE(msg) Alert(msg, __FILE__, __LINE__)

AssetManager* AssetManager::instance = nullptr;

AssetManager::AssetManager() {
	assert(instance == nullptr);
	instance = this;
}

sf::Texture& AssetManager::GetTexture(const std::string& path) {

	std::map<std::string, sf::Texture>& mt = instance->m_texture;
	auto t = mt.find(path);

	if (t == mt.end()) {
		if (!mt[path].loadFromFile(path)) {
			ABORT_TEXTURE(path);
		}
	}
	int x = 2;
	return mt.at(path);
}