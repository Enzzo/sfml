#pragma once

#include "scene_node.h"

#include <SFML/Graphics.hpp>

class Entity : public SceneNode {
	sf::Vector2f velocity_;

public:
	void SetVelocity(sf::Vector2f);
	void SetVelocity(float, float);

	sf::Vector2f GetVelocity() const;
};

class Aircraft : public Entity {
public:
	enum class Type {
		Eagle, Raptor
	};

public:
	explicit Aircraft(Type type);

private:
	Type type_;
};