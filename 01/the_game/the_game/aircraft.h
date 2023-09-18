#pragma once

#include "entity.h"
#include "source_manager.h"

class Aircraft : public Entity {
public:
	enum Type {
		Eagle,
		Raptor
	};

	explicit Aircraft(Type type, const TextureHolder& textures);

private:
	virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Type _type;
	sf::Sprite _sprite;
};