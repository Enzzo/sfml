#include "game.h"

Game::Game() :_window(sf::VideoMode(640, 480), "SFML Application") {
	_player.setRadius(40.f);
	_player.setPosition(100.f, 100.f);
	_player.setFillColor(sf::Color::Cyan);
}

void Game::run() {
	while (_window.isOpen()) {
		ProcessEvents();
		Update();
		Render();
	}
}

void Game::ProcessEvents() {
	sf::Event event;
	while (_window.pollEvent(event)) {

		switch (event.type) {
		case sf::Event::EventType::KeyPressed: {
			HandlePlayerInterrupt(event.key.code, true);
			break;
		}
		case sf::Event::EventType::KeyReleased: {
			HandlePlayerInterrupt(event.key.code, false);
			break;
		}
		case sf::Event::Closed: {
			_window.close();
		}
		}
	}
}

void Game::Update() {

}

void Game::Render() {
	_window.clear();
	_window.draw(_player);
	_window.display();
}

void Game::HandlePlayerInterrupt(sf::Keyboard::Key key, bool is_pressed) {
	if (key == sf::Keyboard::Key::W) {
		is_moving_up = is_pressed;
	}
	if (key == sf::Keyboard::Key::S) {
		is_moving_down = is_pressed;
	}
	if (key == sf::Keyboard::Key::A) {
		is_moving_left = is_pressed;
	}
	if (key == sf::Keyboard::Key::D) {
		is_moving_right = is_pressed;
	}
}