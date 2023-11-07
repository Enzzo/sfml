#pragma once

#include <map>
#include <memory>

#include "SFML/Graphics.hpp"

namespace Textures {
	enum class ID {
		Desert,
		Airplane,
		Missile,
		Eagle,
		Raptor
	};
};

namespace Fonts {
	enum class ID {
		Main
	};
};

template<class resource, class identifier>
class ResourceHolder {
public:
	void load(const identifier, const std::string&);

	template<class parameter>
	void load(const identifier, const std::string&, const parameter&);

	resource& get(identifier) const;

private:
	std::map<identifier, std::unique_ptr<resource>> _src_map;
};

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

 #include "source_manager.inl"