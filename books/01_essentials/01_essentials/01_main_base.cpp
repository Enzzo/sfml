#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"

#include "asset_manager.h"
#include "animator.h"

void init_shape(sf::RectangleShape& shape, const sf::Vector2f& pos, const sf::Color& color);
void handle_player_input();

int main1() {

	sf::RenderWindow window(sf::VideoMode(640, 480), "Title", sf::Style::Default);

	sf::Vector2u w_size = window.getSize();
	sf::View view(sf::FloatRect(0, 0, w_size.x, w_size.y));
	sf::View view2(sf::FloatRect(0, 0, w_size.x, w_size.y));

	//	The view is centered around the world point (0, 0)
	view.setCenter(sf::Vector2f(0, 0));
	view2.setCenter(sf::Vector2f(0, 0));

	view.setViewport(sf::FloatRect(0.0f, 0.0f, 0.5f, 0.5f));
	view2.setViewport(sf::FloatRect(0.5f, 0.5f, 0.5f, 0.5f));

	window.setView(view);
	window.setView(view2);

	window.setFramerateLimit(60);

	sf::Vector2i sprite_size(16, 16);
	sf::Sprite sprite;// (asset_manager::instance()->get_texture("..\\src\\img\\gem_blue.png"));

	sprite.setOrigin(static_cast<sf::Vector2f>(sprite_size) * 0.5f); // sprite origin at it's center
	sprite.setPosition(0, 0);
	sprite.setScale(5, 5);

	sf::CircleShape debug_circle(.5f);
	debug_circle.setPosition(sprite.getPosition());
	debug_circle.setOutlineColor(sf::Color::Red);
	debug_circle.setOutlineThickness(1.0f);

	animator animator(sprite);

	// create an animation and get the reference to it
	animator::animation& walk_up_animation = animator.create_animation("Walk up", "..\\..\\..\\src\\png\\hero.png", sf::seconds(.5f), true);
	animator::animation& walk_down_animation = animator.create_animation("Walk down", "..\\..\\..\\src\\png\\hero.png", sf::seconds(.5f), true);
	animator::animation& walk_right_animation = animator.create_animation("Walk right", "..\\..\\..\\src\\png\\hero.png", sf::seconds(.5f), true);
	animator::animation& walk_left_animation = animator.create_animation("Walk left", "..\\..\\..\\src\\png\\hero.png", sf::seconds(.5f), true);

	// and frames in the animation
	walk_up_animation.add_frames(sf::Vector2i(0, 0), sprite_size, 4);
	walk_down_animation.add_frames(sf::Vector2i(64, 0), sprite_size, 4);
	walk_right_animation.add_frames(sf::Vector2i(64, 16), sprite_size, 4);
	walk_left_animation.add_frames(sf::Vector2i(0, 16), sprite_size, 4);

	sf::Clock clock;

	while (window.isOpen()) {

		sf::Time delta_time = clock.restart();

		animator.update(delta_time);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Key::W: {
					if (animator.get_current_animator_name() != "Walk up") {
						animator.switch_animation("Walk up");
					}
					sprite.move(0, -4);
					break;
				}
				case sf::Keyboard::Key::S: {
					if (animator.get_current_animator_name() != "Walk down") {
						animator.switch_animation("Walk down");
					}
					sprite.move(0, 4);
					break;
				}
				case sf::Keyboard::Key::D: {
					if (animator.get_current_animator_name() != "Walk right") {
						animator.switch_animation("Walk right");
					}
					sprite.move(4, 0);
					break;
				}
				case sf::Keyboard::Key::A: {
					if (animator.get_current_animator_name() != "Walk left") {
						animator.switch_animation("Walk left");
					}
					sprite.move(-4, 0);
					break;
				}
				}

			}
		}

		window.clear();
		window.draw(sprite);
		window.draw(debug_circle);
		window.display();
	}

	return EXIT_SUCCESS;
}

void init_shape(sf::RectangleShape& shape, const sf::Vector2f& pos, const sf::Color& color) {
	shape.setFillColor(color);
	shape.setPosition(pos);
	shape.setOrigin(shape.getSize() * .5f);
}

void handle_player_input() {

}