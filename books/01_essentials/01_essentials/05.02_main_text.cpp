#include <SFML/Graphics.hpp>

#include <asset_manager.h>

int main52() {

	sf::RenderWindow window(sf::VideoMode(640, 480), "Text", sf::Style::Default);

	sf::Text text("Посмотри на этот шрифт.", asset_manager::instance()->get_font("../../../src/fnt/DPix_8pt.ttf"));

	text.setString(std::string("Посмотри на этот шрифт."));
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	while (window.isOpen()) {
		sf::Event ev;

		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();

		window.draw(text);

		window.display();
	}

	return 0;
}