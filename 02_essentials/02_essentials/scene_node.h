#pragma once
#include "SFML/Graphics.hpp"

#include <memory>
#include <vector>

class SceneNode : public sf::Transformable, public sf::Drawable,
				  private sf::NonCopyable {
public: 
	typedef std::unique_ptr<SceneNode> Ptr;

public:
	SceneNode();

	void AttachChild(Ptr);
	Ptr DetachChild(const SceneNode&);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	std::vector<Ptr> children_;
	SceneNode* parent_;
};