#include "game.h"

Game::Game() :	_window(sf::VideoMode(640, 480), "Title"),
				_texture(),
				_player(),
				_is_moving_up(false),
				_is_moving_down(false),
				_is_moving_left(false),
				_is_moving_right(false),
				_player_speed(50000.0f),
				_time_per_frame(sf::seconds(1.f/60.f))
{
	if (!_texture.loadFromFile("D:\\dev\\git\\sfml\\src\\png\\Eagle.png")) {
		//	invalid texture handling
	}
	_player.setTexture(_texture);
	_player.setPosition(200.0f, 200.0f);
}

void Game::run() {
	sf::Clock clock;
	sf::Time time_since_last_update = sf::Time::Zero;
	proccess_events();
	while (_window.isOpen()) {
		time_since_last_update += clock.restart();

		while (time_since_last_update > _time_per_frame) {
			time_since_last_update -= _time_per_frame;
			proccess_events();
			update(time_since_last_update);
		}		
		render();
	}
}

void Game::proccess_events() {
	sf::Event event;
	while (_window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::KeyPressed:
				handle_player_input(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handle_player_input(event.key.code, false);
				break;
			case sf::Event::Closed:
				_window.close();
				break;
		}
	}
}

void Game::handle_player_input(const sf::Keyboard::Key& key, bool is_pressed) {
	switch (key) {
	case sf::Keyboard::Key::W:
		_is_moving_up = is_pressed;
		break;
	case sf::Keyboard::Key::S:
		_is_moving_down = is_pressed;
		break;
	case sf::Keyboard::Key::A:
		_is_moving_left = is_pressed;
		break;
	case sf::Keyboard::Key::D:
		_is_moving_right = is_pressed;
		break;
	}
}

void Game::update(const sf::Time& deltaTime) {
	sf::Vector2f movement(.0f, .0f);
	if (_is_moving_up) movement.y -= _player_speed;
	if (_is_moving_down) movement.y += _player_speed;
	if (_is_moving_left) movement.x -= _player_speed;
	if (_is_moving_right) movement.x += _player_speed;

	_player.move(movement * deltaTime.asSeconds());
}

void Game::render() {
	_window.clear();
	_window.draw(_player);
	_window.display();
}