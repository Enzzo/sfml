#include "game.h"
#include "command_queue.h"

//--------------------------------------------------+
//					class Game						|
//--------------------------------------------------+
//					Game							|
//--------------------------------------------------+
Game::Game() :	_window(sf::VideoMode(640, 480), "Title"),
				_texture(),
				_player(),
				_world(_window),
				_is_moving_up(false),
				_is_moving_down(false),
				_is_moving_left(false),
				_is_moving_right(false),
				_is_paused(false),
				_is_closed(false),
				_player_speed(500.0f),
				_time_per_frame(sf::seconds(1.f/60.f))
{
	if (!_texture.loadFromFile("D:\\dev\\git\\sfml\\src\\png\\Eagle.png")) {
		//	invalid texture handling
	}
	_player.setTexture(_texture);
	_player.setPosition(200.0f, 200.0f);
}

//--------------------------------------------------+
//					class Game						|
//--------------------------------------------------+
//					void run						|
//--------------------------------------------------+
void Game::run() {
	sf::Clock clock;
	sf::Time time_since_last_update = sf::Time::Zero;

	while (_window.isOpen()) {
		time_since_last_update += clock.restart();

		while (time_since_last_update > _time_per_frame) {
			time_since_last_update -= _time_per_frame;
			proccess_events();
			
			if (!_is_paused) {
				update(_time_per_frame);
			}
		}		
		render();
	}
}

//--------------------------------------------------+
//					class Game						|
//--------------------------------------------------+
//				void proccess_events				|
//--------------------------------------------------+
void Game::proccess_events() {
	sf::Event event;
	while (_window.pollEvent(event)) {
		if (_is_closed) {
			_window.close();
		}
		switch (event.type) {
			case sf::Event::KeyPressed:
				handle_player_input(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handle_player_input(event.key.code, false);
				break;
			case sf::Event::GainedFocus:
				_is_paused = false;
				break;
			case sf::Event::LostFocus:
				_is_paused = true;
				break;
			case sf::Event::Closed:
				_window.close();
				break;
		}
	}
}

//--------------------------------------------------+
//					class Game						|
//--------------------------------------------------+
//				void handle_player_input			|
//--------------------------------------------------+
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
	case sf::Keyboard::Key::Escape:
		_is_closed = is_pressed;
		break;
	}
}

//--------------------------------------------------+
//					class Game						|
//--------------------------------------------------+
//					void update						|
//--------------------------------------------------+
void Game::update(const sf::Time deltaTime) {
	sf::Vector2f movement(.0f, .0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		movement.y -= _player_speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		movement.y += _player_speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		movement.x -= _player_speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		movement.x += _player_speed;
	}

	_player.move(movement * deltaTime.asSeconds());

	sf::Vector2i window_center(_window.getSize() / 2u);
	sf::Vector2i mouse_position = sf::Mouse::getPosition(_window);
	sf::Vector2i delta = window_center - mouse_position;
	sf::Mouse::setPosition(window_center, _window);
}

//--------------------------------------------------+
//					class Game						|
//--------------------------------------------------+
//					void render						|
//--------------------------------------------------+
void Game::render() {
	_window.clear();

	// TODO моё решение -
	// _window.draw(_player);
	_window.display();
}

//--------------------------------------------------+
//					class Game						|
//--------------------------------------------------+
//				void process_input					|
//--------------------------------------------------+
void Game::proccess_input() {
	CommandQueue& commands = _world.get_command_queue();

	sf::Event event;
	while (_window.pollEvent(event)) {
		_player.handle_event(event, commands);

		if (event.type == sf::Event::Closed) {
			_window.close();
		}

		_player.handle_realtime_input(commands);
	}
}