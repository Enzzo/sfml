#include "application.h"

//	+---------------------------------------------------+
//	|				class Application					|
//	+---------------------------------------------------+
//	|				Constructor							|
//	+---------------------------------------------------+
Application::Application() {
	_state_stack.push_state(States::Title);
}

//	+---------------------------------------------------+
//	|				class Application					|
//	+---------------------------------------------------+
//	|				void register_states()				|
//	+---------------------------------------------------+
void Application::register_states() {
	_state_stack.register_state<TitleState>(States::Title);
	_state_stack.register_state<MenuState>(States::Menu);
	_state_stack.register_state<GameState>(States::Game);
	_state_stack.register_state<PauseState>(States::Pause);
}

//	+---------------------------------------------------+
//	|				class Application					|
//	+---------------------------------------------------+
//	|				void process_input()				|
//	+---------------------------------------------------+
void Application::proccess_input() {
	sf::Event event;
	
	while (_window.pollEvent(event)) {
		_state_stack.handle_event(event);
	}

	if (_state_stack.is_empty()) {
		_window.close();
	}
}

//	+---------------------------------------------------+
//	|				class Application					|
//	+---------------------------------------------------+
//	|				void update()						|
//	+---------------------------------------------------+
void Application::update(sf::Time dt) {
	_state_stack.update(dt);
}

//	+---------------------------------------------------+
//	|				class Application					|
//	+---------------------------------------------------+
//	|				void draw()				|
//	+---------------------------------------------------+
void Application::draw() {
	_state_stack.draw();
}