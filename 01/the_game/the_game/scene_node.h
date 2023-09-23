#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <cassert>

#include "SFML/Graphics.hpp"

//--------------------------------------------------+
//					struct Command					|
//--------------------------------------------------+
class SceneNode;
struct Command {
	Command() {};
	std::function<void(SceneNode&, sf::Time)> action;
	unsigned int category;
};

//--------------------------------------------------+
//					derived_action					|
//--------------------------------------------------+
template<typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derived_action(Function fn) {
	return [=](SceneNode& node, sf::Time dt) {
		// Check if cast is safe
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		//Downcast node and invoke function on it
		fn(static_cast<GameObject&>(node), dt);
	};
};

//--------------------------------------------------+
//					namespace Category				|
//--------------------------------------------------+
//					enum Type	 					|
//--------------------------------------------------+
namespace Category {
	enum Type {
		None = 0,
		Scene = 1 << 0,
		PlayerAircraft = 1 << 1,
		AlliedAircraft = 1 << 2,
		EnemyAircraft = 1 << 3
	};
};

//--------------------------------------------------+
//					class SceneNode					|
//--------------------------------------------------+
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

	inline unsigned int get_category() const;
	void on_command(const Command&, sf::Time);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states)const;

	virtual void update_current(const sf::Time);
	void update_children(const sf::Time);

private:
	SceneNode* _parent;
	std::vector<ptr> _children;
};