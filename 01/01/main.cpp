#include <sfml/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>

void initRect(sf::RectangleShape&, const sf::Vector2f&, const sf::Color&);
void DrawRects(sf::RenderWindow&, const std::vector<sf::RectangleShape>&);
void ShowGUI(sf::RenderWindow&, const std::vector<std::string>&);

int main() {

	sf::RenderWindow window(sf::VideoMode(640, 480), "Title");

	window.setFramerateLimit(60);

	sf::Vector2f startPos(50, 50);

	sf::RectangleShape playerRect(sf::Vector2f(50, 50));
	sf::RectangleShape targetRect(sf::Vector2f(50, 50));
	sf::RectangleShape badRect(sf::Vector2f(50, 100));
	
	float speed = 6.0;
	initRect(playerRect, startPos, sf::Color::Green);
	initRect(targetRect, sf::Vector2f(400, startPos.y), sf::Color::Yellow);
	initRect(badRect, sf::Vector2f(300, startPos.y), sf::Color::Red);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				playerRect.move(speed * static_cast<float>(std::cos(playerRect.getRotation())), speed * static_cast<float>(std::sin(playerRect.getRotation())));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				playerRect.move(0, 1*speed);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				playerRect.rotate(-10.0f);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				playerRect.rotate(10.0f);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();

			if(playerRect.getGlobalBounds().intersects(targetRect.getGlobalBounds()))
				window.close();
			if (playerRect.getGlobalBounds().intersects(badRect.getGlobalBounds()))
				playerRect.setPosition(startPos);

		}
		window.clear();
		//DrawRects(window, { playerRect, targetRect, badRect });
		//ShowGUI(window, { ftoa(8), "asdf fddff" });
		window.display();
	}
	std::cout << std::cos(90);
	return 0;
}

void initRect(sf::RectangleShape& rect, const sf::Vector2f& pos, const sf::Color& color) {
	rect.setOrigin(rect.getSize() * .5f);
	rect.setPosition(pos);
	rect.setFillColor(color);
}

void DrawRects(sf::RenderWindow& rw, const std::vector<sf::RectangleShape>& rs) {
	for (const auto& r : rs) {
		rw.draw(r);
	}
}

void ShowGUI(sf::RenderWindow& rw, const std::vector<std::string>& info) {
	sf::Font font;
	font.loadFromFile("Arial.ttf");
	int y = 5;
	int offset = 15;
	for (const std::string& s : info) {
		sf::Text t(s, font, 14);
		t.setPosition(5, y+=offset);
		t.setFillColor(sf::Color::White);
		rw.draw(t);
	}
}