#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"

void init_shape(sf::RectangleShape& shape, const sf::Vector2f& pos, const sf::Color& color);

int main() {

	sf::RenderWindow window(sf::VideoMode(640, 480), "Title", sf::Style::Default);

	window.setFramerateLimit(60);

	sf::String buffer;

	sf::CircleShape circle_shape(50);
	circle_shape.setFillColor(sf::Color::Red);
	circle_shape.setOutlineColor(sf::Color::White);
	circle_shape.setOutlineThickness(3);

	sf::RectangleShape rect_shape(sf::Vector2f(50, 50));
	rect_shape.setFillColor(sf::Color::Green);

	sf::ConvexShape triangle;
	triangle.setPointCount(3);
	triangle.setPoint(0, sf::Vector2f(100, 0));
	triangle.setPoint(1, sf::Vector2f(0, 100));
	triangle.setPoint(2, sf::Vector2f(100, 100));
	triangle.setFillColor(sf::Color::Blue);

	sf::RectangleShape rect(sf::Vector2f(50, 50));
	rect.setFillColor(sf::Color::Red);
	rect.setOrigin(sf::Vector2f(25, 25));
	rect.setPosition(sf::Vector2f(50, 50));

	sf::Vector2f start_pos = sf::Vector2f(50, 50);
	
	sf::RectangleShape player_rect(sf::Vector2f(50, 50));
	init_shape(player_rect, start_pos, sf::Color::Green);

	sf::RectangleShape target_rect(sf::Vector2f(50, 50));
	init_shape(target_rect, sf::Vector2f(400, 50), sf::Color::Blue);

	sf::RectangleShape bad_rect(sf::Vector2f(50, 100));
	init_shape(bad_rect, sf::Vector2f(250, 50), sf::Color::Red);

	const unsigned int width = 5, height = 5;
	sf::Uint8 pixels[width * height * 4] = {
		255, 255, 255, 255,	//white
		0, 0, 0, 0,			//black
		255, 0, 0, 255,		//red
		128, 128, 128, 255	//gray
	};

	sf::Image image;
	image.create(width, height, pixels);

	image.saveToFile("1.jpg");

	bool moving = false;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {

			switch (event.type) {
			case sf::Event::Closed: {
				window.close();
				break;
			}
			case sf::Event::LostFocus: {
				std::cerr << "Window lost focus\n";
				break;
			}
			case sf::Event::GainedFocus: {
				std::cerr << "Window gained focus\n";
				break;
			}
			case sf::Event::TextEntered: {
				std::cerr << "Text entered\n";
				buffer += event.text.unicode;

				break;
			}
			case sf::Event::KeyPressed: {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				if (event.key.code == sf::Keyboard::BackSpace) {
					int size = buffer.getSize();
					if (size > 0) {
						buffer.erase(size - 1, 1);
					}
				}
				if (event.key.code == sf::Keyboard::Right) {
					moving = true;
				}
				break;
			}
			case sf::Event::KeyReleased: {
				if (event.key.code == sf::Keyboard::Return) {
					window.setTitle(buffer);
					buffer.clear();
				}
				if (event.key.code == sf::Keyboard::Right) {
					moving = false;
				}
				break;
			}
			}		
		}

		if (moving) {
			rect.rotate(1.5f);
			rect.move(sf::Vector2f(1, 0));
		}

		player_rect.move(1, 0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
			player_rect.move(0, 1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
			player_rect.move(0, -1);
		}

		if (player_rect.getGlobalBounds().intersects(target_rect.getGlobalBounds())) {
			window.close();
		}
		if (player_rect.getGlobalBounds().intersects(bad_rect.getGlobalBounds())) {
			player_rect.setPosition(start_pos);
		}

		window.clear();

		//window.draw(circle_shape);
		//window.draw(rect_shape);
		//window.draw(triangle);
		//window.draw(rect);

		//window.draw(player_rect);
		//window.draw(target_rect);
		//window.draw(bad_rect);

		window.display();
	}

	return EXIT_SUCCESS;
}

void init_shape(sf::RectangleShape& shape, const sf::Vector2f& pos, const sf::Color& color) {
	shape.setFillColor(color);
	shape.setPosition(pos);
	shape.setOrigin(shape.getSize() * .5f);
}