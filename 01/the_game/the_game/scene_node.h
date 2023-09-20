#pragma once

#include <vector>
#include <memory>

#include "SFML/Graphics.hpp"

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable{
public:
	typedef std::unique_ptr<SceneNode> ptr;

public:
	SceneNode() {};
	
	void attach_child(ptr child);
	ptr detach_child(const SceneNode& child);

	void update(const sf::Time);

	sf::Transform get_world_transform() const;
	sf::Vector2f get_world_position() const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states)const;

	virtual void update_current(const sf::Time);
	void update_children(const sf::Time);

private:
	SceneNode* _parent;
	std::vector<ptr> _children;
};