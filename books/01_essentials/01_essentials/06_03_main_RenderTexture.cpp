#include <iostream>

#include <SFML/Graphics.hpp>

#include <asset_manager.h>

int main0603() {

	sf::RenderWindow window(sf::VideoMode(800, 600), "Pixelation");

	if (!sf::Shader::isAvailable()) {
		std::cerr << "Shader is not available";
		return -1;	// Shaders are not supported. Abort!
	}

	sf::RenderTexture r_texture;
	sf::Vector2<unsigned int> wsize = window.getSize();
	r_texture.create(wsize.x, wsize.y);

	// The sprite used for post-processing the texture
	sf::Sprite pp_sprite(r_texture.getTexture());

	sf::Shader* shader = asset_manager::instance()->get_shader("../../../src/sdr/vertShader.vert", "../../../src/sdr/pixelationShader.frag");

	shader->setUniform("uTexture", r_texture.getTexture());
	shader->setUniform("uTextureSize", static_cast<sf::Vector2f>(r_texture.getSize()));
	shader->setUniform("uPixelSize", 8.f);

	sf::Sprite sprite(asset_manager::instance()->get_texture("../../../src/png/scull.png"));

	while (window.isOpen()) {
		sf::Event ev;
		while (window.pollEvent(ev)) {}

		// update

		// render frame

		r_texture.clear(); {
			// draw scene here
		}

		r_texture.display();

		window.clear(); {
			// post processing by applying the shader to the RenderTexture
			window.draw(pp_sprite, shader);
		}

		window.display();
	}

	return 0;
}