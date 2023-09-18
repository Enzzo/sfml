#pragma once

#include <map>
#include <memory>

#include "SFML/Graphics.hpp"

namespace Textures {
	enum ID {
		Landscape,
		Airplane,
		Missile,
		Eagle,
		Raptor
	};	
}
template<class resource, class identifier>
class ResourceHolder {
public:
	void load(const identifier, const std::string&);

	template<class parameter>
	void load(const identifier, const std::string&, const parameter&);

	resource& get(identifier) const;

private:
	std::map<identifier, std::unique_ptr<resource>> _texture_map;
};

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

 #include "source_manager.inl"