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
		if (event.type == sf::Event::Closed) {
			_window.close();
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