#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>

namespace Textures {
	enum ID {
		Landscape,
		Airplane,
		Missile
	};
}

class TextureHolder {
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> texture_map_;

public:
	void Load(Textures::ID, const std::string&);
	const sf::Texture& Get(Textures::ID)const;

};