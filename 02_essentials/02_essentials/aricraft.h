#pragma once
#include "entity.h"
#include "resource_holder.h"

class Aircraft : public Entity {
public:
	enum Type {
		Eagle, Raptor
	};

public:
	explicit Aircraft(Type, const TextureHolder&);
	
private:
	virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;

private:
	Type mType;
	sf::Sprite mSprite;
};