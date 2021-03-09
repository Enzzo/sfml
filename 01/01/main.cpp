#include <sfml/Graphics.hpp>
#include <vector>

void initRect(sf::RectangleShape&, const sf::Vector2f&, const sf::Color&);
void DrawRects(sf::RenderWindow&, const std::vector<sf::RectangleShape>&);

int main() {

	sf::RenderWindow window(sf::VideoMode(640, 480), "Title");

	window.setFramerateLimit(60);

	sf::Vector2f startPos(50, 50);

	sf::RectangleShape playerRect(sf::Vector2f(50, 50));
	sf::RectangleShape targetRect(sf::Vector2f(50, 50));
	sf::RectangleShape badRect(sf::Vector2f(50, 100));

	initRect(playerRect, startPos, sf::Color::Green);
	initRect(targetRect, sf::Vector2f(350, startPos.y), sf::Color::Yellow);
	initRect(badRect, sf::Vector2f(200, startPos.y), sf::Color::Red);

	while (window.isOpen()) {
		sf::Event event;
		playerRect.move(1, 0);
		while (window.pollEvent(event)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				playerRect.move(0, -1);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				playerRect.move(0, 1);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();

			//if(playerRect.getGlobalBounds())
		}
		window.clear();
		DrawRects(window, { playerRect, targetRect, badRect });
		window.display();
	}

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