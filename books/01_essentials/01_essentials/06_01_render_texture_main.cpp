#include <iostream>

#include <SFML/Graphics.hpp>

int main0601() {

	sf::RenderTexture r_texture;

	
	// deprecated
	// r_texture.create(32, 32, /*depth buffer enabled = */ false);
	r_texture.create(32, 32, /*depth buffer enabled = */ sf::ContextSettings{});

	sf::CircleShape circle(16); // circle radius 16

	// render routine - clear -> draw -> display

	r_texture.clear();
	r_texture.draw(circle);
	r_texture.display();

	// RenderTexture::getTexture() gets a ref to the Texture object
	sf::Sprite sprite(r_texture.getTexture());

	return 0;
}