#include "entity.h"

//--------------------ENTITY-----------------------
void Entity::SetVelocity(sf::Vector2f velocity) {
	velocity_ = velocity;
}

void Entity::SetVelocity(float vx, float vy) {
	velocity_.x = vx; velocity_.y = vy;
}

sf::Vector2f Entity::GetVelocity() const {
	return velocity_;
}

//--------------------AIRCRAFT-----------------------
Aircraft::Aircraft(Type type) : type_(type) {}