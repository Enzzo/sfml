#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Glsl.hpp>

#include <asset_manager.h>

int main0602() {

	sf::RenderWindow window(sf::VideoMode(640, 480), "Shaders", sf::Style::Default);

	if (!sf::Shader::isAvailable()) {
		std::cerr << "Shader is not supported. Abort!";
		return -1;
	}

//	+-------------------------------------------------------------------+
//	|	загрузка шейдеров из файлов: (РЕКОМЕНДУЕМЫЙ СПОСОБ)				|
//	+-------------------------------------------------------------------+
	sf::Shader shader1;													
	if (!shader1.loadFromFile("../../../src/sdr/vertShader.vert", "../../../src/sdr/fragShader.frag")) {	
		std::cerr << "failed to load shaders from file";							
		return -1;														
	}																	


//	+-------------------------------------------------------------------+
//	|	загрузка шейдеров из кода:										|
//	+-------------------------------------------------------------------+
	std::string vert_shader =
		"void main(){" \
		"gl_Position = gl_Vertex;" \
		"}";

	std::string frag_shader =
		"void main(){" \
		"gl_FragColor = vec4(1, 0, 0, 1);" \
		"}";

	sf::Shader shader2;
	if (!shader2.loadFromMemory(vert_shader, frag_shader)) {
		std::cerr << "failed to load shaders from memory";
		return -2;
	}

//	+-------------------------------------------------------------------+
//	|	загрузка шейдеров из файлов:									|
//	+-------------------------------------------------------------------+

	sf::Shader* shader3 = asset_manager::instance()->get_shader("../../../src/sdr/vertShader.vert", "../../../src/sdr/fragShader.frag");
	
	// deprecated
	// shader3->setParameter("uSpecialVector", sf::Vector2f(3, 3));
	shader3->setUniform("uSpecialVector", sf::Glsl::Vec2(3, 3));

	sf::Shader* shader = asset_manager::instance()->get_shader("../../../src/sdr/vertShader.vert", "../../../src/sdr/rippleShader.frag");
	
	sf::Sprite sprite(asset_manager::instance()->get_texture("../../../src/png/scull.png"));

	shader->setUniform("uTexture", *sprite.getTexture());
	shader->setUniform("uPositionFreq", 0.1f);
	shader->setUniform("uSpeed", 20.f);
	shader->setUniform("uStrength", 0.03f);

	sf::Shader::bind(shader);

	sf::Clock clock;

	while (window.isOpen()) {
		sf::Event ev;

		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				window.close();
			}
			if (ev.type == sf::Event::KeyPressed) {
				if (ev.key.code == sf::Keyboard::Space) {
					window.close();
				}
			}
		}

		window.clear();

		shader->setUniform("uTime", clock.getElapsedTime().asSeconds());

		window.draw(sprite, shader);
		window.display();
	}

	sf::Shader::bind(nullptr);

	return 0;
}