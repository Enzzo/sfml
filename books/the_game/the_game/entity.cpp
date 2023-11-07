#include "entity.h"

void Entity::set_velocity(const float x, const float y) {
	_velocity = { x, y };
}

void Entity::set_velocity(const sf::Vector2f v) {
	_velocity = v;
}

void Entity::update_current(const sf::Time delta_time) {
	move(_velocity * delta_time.asSeconds());
}

sf::Vector2f Entity::get_velocity() const {
	return _velocity;
}