#include "node.h"
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