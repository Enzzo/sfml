#pragma once

#include "scene_node.h"

#include <SFML/Graphics.hpp>

class Entity : public SceneNode {
	sf::Vector2f velocity_;

public:
	//Entity() = default;

	void SetVelocity(sf::Vector2f);
	void SetVelocity(float, float);

	sf::Vector2f GetVelocity() const;

private:
	virtual void updateCurrent(sf::Time) override;
};