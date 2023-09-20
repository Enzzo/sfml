#pragma once

#include "SFML/Graphics.hpp"

#include "sprite_node.h"

class Entity : public SceneNode {
public:

	Entity() {};

	void set_velocity(const float, const float);
	void set_velocity(const sf::Vector2f);

	virtual void update_current(const sf::Time) override;

	inline const sf::Vector2f get_velocity() const;

private:
	sf::Vector2f _velocity;
};