#include "entity.h"

void Entity::set_velocity(const float x, const float y) {
	_velocity = { x, y };
}

void Entity::set_velocity(const sf::Vector2f v) {
	_velocity = v;
}

const sf::Vector2f Entity::get_velocity() const {
	return _velocity;
}