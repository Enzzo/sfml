#include "sprite_node.h"
#include <assert.h>

void SceneNode::attach_child(ptr child) {
	child->_parent = this;
	_children.push_back(std::move(child));
}

SceneNode::ptr SceneNode::detach_child(const SceneNode& node) {
	auto found = std::find_if(_children.begin(), _children.end(), [&](const ptr& p) {
		return p.get() == &node;
		});
	assert(found != _children.end());
	ptr result =  std::move(*found);
	result->_parent = nullptr;
	_children.erase(found);
	return result;
}

void SceneNode::update(const sf::Time delta_time) {
	update_current(delta_time);
	update_children(delta_time);
}

sf::Transform SceneNode::get_world_transform() const {
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->_parent) {
		transform = node->getTransform() * transform;
	}
	
	return transform;
}

sf::Vector2f SceneNode::get_world_position() const {
	return get_world_transform() * sf::Vector2f();
}

//--------------------------------------------------+
//					class SceneNode					|
//--------------------------------------------------+
//					void get_category()	 			|
//--------------------------------------------------+
unsigned int SceneNode::get_category() const {
	return Category::Scene;
}

//--------------------------------------------------+
//					class SceneNode					|
//--------------------------------------------------+
//					void on_command					|
//--------------------------------------------------+
void SceneNode::on_command(const Command& command, sf::Time dt) {
	if (command.category & get_category()) {
		command.action(*this, dt);
	}

	for (ptr& child : _children) {
		child->on_command(command, dt);
	}
}

//--------------------------------------------------+
//					class SceneNode					|
//--------------------------------------------------+
//					void draw()	 					|
//--------------------------------------------------+
void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	draw_current(target, states);

	for (const ptr& child : _children) {
		child->draw(target, states);
	}
}

void SceneNode::draw_current(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const ptr& p : _children) {
		target.draw(*p, states);
	}
}

void SceneNode::update_current(const sf::Time delta_time) {

}

void SceneNode::update_children(const sf::Time delta_time) {
	for (const ptr& child : _children) {
		child->update(delta_time);
	}
}