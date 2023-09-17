#pragma once

#include <vector>
#include <memory>

#include "SFML/Graphics.hpp"

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable{
public:
	typedef std::unique_ptr<SceneNode> ptr;

public:
	SceneNode();
	void attach_child(ptr child);
	ptr detach_child(const SceneNode& child);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	void draw_current(sf::RenderTarget& target, sf::RenderStates states)const;

private:
	SceneNode* _parent;
	std::vector<ptr> _children;
};