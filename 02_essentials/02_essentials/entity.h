#pragma once

#include "scene_node.h"

#include <SFML/Graphics.hpp>

class Entity : public SceneNode {
	sf::Vector2f mVelocity;

public:

	void setVelocity(sf::Vector2f);
	void setVelocity(float, float);

	sf::Vector2f getVelocity() const;

private:
	virtual void updateCurrent(sf::Time) override;
};