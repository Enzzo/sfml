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

void SceneNode::update(sf::Time dt) {
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time) {}

void SceneNode::updateChildren(sf::Time dt) {
	for (const Ptr& child : children_) {
		child->update(dt);
	}
}

sf::Transform SceneNode::getWorldTransform() const {
	sf::Transform transform = sf::Transform::Identity;
	for (const SceneNode* node = this; node != nullptr; node = node->parent_) {
		transform = node->getTransform() * transform;
	}
	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const {
	return getWorldTransform() * sf::Vector2f();
}