#pragma once

#include "state_stack.h"

//	+---------------------------------------------------+
//	|				class Application					|
//	+---------------------------------------------------+
class Application {
public:
	Application();

	void register_states();
	void proccess_input();
	void update(sf::Time);
	void draw();

private:
	sf::RenderWindow _window;
	StateStack _state_stack;
};