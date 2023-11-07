#pragma once

#include "scene_node.h"

//--------------------------------------------------+
//					class SpriteNode				|
//--------------------------------------------------+

class SpriteNode : public SceneNode {
public:
	explicit SpriteNode(const sf::Texture& texture) {};
	SpriteNode(const sf::Texture& texture, const sf::IntRect& rect) {};

private:
	virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Sprite _sprite;
};