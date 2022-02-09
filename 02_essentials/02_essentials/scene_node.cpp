#include "scene_node.h"

#include <cassert>

void SceneNode::AttachChild(Ptr child) {
	child->parent_ = this;
	children_.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::DetachChild(const SceneNode& node) {
	auto found = std::find_if(children_.begin(), children_.end(), [&](Ptr& p)->bool {return p.get() == &node; });
	assert(found != children_.end());

	Ptr result = std::move(*found);
	result->parent_ = nullptr;
	children_.erase(found);
	return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	
	drawCurrent(target, states);
	
	for (const Ptr& child : children_) {
		child->draw(target, states);
	}
}