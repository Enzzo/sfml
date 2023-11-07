#pragma once

#include "entity.h"
#include "source_manager.h"

//--------------------------------------------------+
//					class Aircraft					|
//--------------------------------------------------+
class Aircraft : public Entity {
public:
	enum Type {
		Eagle,
		Raptor
	};

	explicit Aircraft(Type type, const TextureHolder& textures);

	void accelerate(sf::Vector2f);

	inline unsigned int get_category() const;

private:
	virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Type _type;
	sf::Sprite _sprite;
};

//--------------------------------------------------+
//				struct AircraftMover				|
//--------------------------------------------------+
struct AircraftMover {
	AircraftMover(float vx, float vy) : velocity(vx, vy){}
	
	void operator()(Aircraft& aircraft, sf::Time dt) const {
		// Aircraft& aircraft = static_cast<Aircraft&>(node);
		aircraft.accelerate(velocity);
	}

	sf::Vector2f velocity;
};