#pragma once

#include "scene_node.h"

class SpriteNode : public SceneNode {
	sf::Sprite mSprite;

public:
	explicit SpriteNode(const sf::Texture&);
	SpriteNode(const sf::Texture&, const sf::IntRect&);

private:
	virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;
};