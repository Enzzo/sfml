#include "source_manager.h"
#include <cassert>

void TextureHolder::Load(Textures::ID id, const std::string& filename) {
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	if (!texture->loadFromFile(filename)) {
		throw std::runtime_error("TextureHolder::Load - Failed to load " + filename);
	}
	auto inserted = texture_map_.insert(std::make_pair(id, std::move(texture)));
	assert(inserted.second);
}

const sf::Texture& TextureHolder::Get(Textures::ID id)const{
	auto found = texture_map_.find(id);
	assert(found != texture_map_.end());
	return *found->second;
}