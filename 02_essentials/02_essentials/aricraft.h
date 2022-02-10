#pragma once
#include "entity.h"
#include "source_manager.h"

class Aircraft : public Entity {
public:
	enum class Type {
		Eagle, Raptor
	};

public:
	explicit Aircraft(Type type, const TextureHolder& textures);
	void drawCurrent(sf::RenderTarget&, sf::RenderStates) const override;

private:
	Type type_;
	sf::Sprite sprite_;
};