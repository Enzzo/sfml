#pragma once

#include "SFML/Graphics.hpp"

class Entity {
public:
	void set_velocity(const float, const float);
	void set_velocity(const sf::Vector2f);

	inline const sf::Vector2f get_velocity() const;

private:
	sf::Vector2f _velocity;
};