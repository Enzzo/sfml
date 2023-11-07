#include "state.h"

//	+---------------------------------------------------+
//	|				class TitleState					|
//	+---------------------------------------------------+
//	|				bool handle_event					|
//	+---------------------------------------------------+
bool TitleState::handle_event(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		request_stack_pop();
		request_stack_push(States::Menu);
	}

	return true;
}

//	+---------------------------------------------------+
//	|				class TitleState					|
//	+---------------------------------------------------+
//	|				bool update							|
//	+---------------------------------------------------+
bool TitleState::update(sf::Time dt) {
	_text_effect_time += dt;

	if (_text_effect_time >= sf::seconds(0.5f)) {
		_show_text = !_show_text;
		_text_effect_time = sf::Time::Zero;
	}

	return true;
}

//	+---------------------------------------------------+
//	|				class MenuState						|
//	+---------------------------------------------------+
//	|				Constructor							|
//	+---------------------------------------------------+
MenuState::MenuState(StateStack& stack, Context context) {
	sf::Text play_option;

	// TODO: убрал
	// play_option.setFont(font);
	play_option.setString("Play");
	
	// TODO: убрал
	// center_origin(play_option);
	play_option.setPosition(context.window->getView().getSize() / 2.f);
	_options.push_back(play_option);
}

//	+---------------------------------------------------+
//	|				class MenuState						|
//	+---------------------------------------------------+
//	|			void update_option_text					|
//	+---------------------------------------------------+
void MenuState::update_option_text() {
	if (_options.empty()) {
		return;
	}

	// while all texts
	for (sf::Text& text : _options) {
		text.setColor(sf::Color::White);
	}

	// red the selected text
	_options[_option_index].setColor(sf::Color::Red);
}

//	+---------------------------------------------------+
//	|				class MenuState						|
//	+---------------------------------------------------+
//	|				void handle_event					|
//	+---------------------------------------------------+
void MenuState::handle_event(sf::Event event) {

	if (event.key.code == sf::Keyboard::Up) {
		if (_option_index > 0) {
			_option_index--;
		}
		else {
			_option_index = _options.size() - 1;
		}

		update_option_text();
	}
	else if (event.key.code == sf::Keyboard::Down) {
		if (_option_index < _options.size() - 1) {
			_option_index++;
		}
		else {
			_option_index = 0;
		}

		update_option_text();
	}

	if (event.key.code == sf::Keyboard::Return) {
		if (_option_index == Play) {
			request_stack_pop();
			request_stack_push(States::Game);
		}
		else if (_option_index == Exit) {
			request_stack_pop();
		}
	}
}

//	+---------------------------------------------------+
//	|				class PauseState					|
//	+---------------------------------------------------+
//	|				void draw							|
//	+---------------------------------------------------+
void PauseState::draw() {
	//	TODO: убрал
	// sf::RenderWindow& window = *getContext().window;
	// TODO: добавил
	sf::RenderWindow window;
	window.setView(window.getDefaultView());

	sf::RectangleShape background_shape;
	background_shape.setFillColor(sf::Color(0, 0, 0, 150));
	background_shape.setSize(sf::Vector2f(window.getSize()));

	window.draw(background_shape);
	window.draw(_paused_text);
	window.draw(_instruction_text);
}
//	+---------------------------------------------------+
//	|				class PauseState					|
//	+---------------------------------------------------+
//	|				bool update							|
//	+---------------------------------------------------+
bool PauseState::update(sf::Time dt) {
	return false;
}

//	+---------------------------------------------------+
//	|				class PauseState					|
//	+---------------------------------------------------+
//	|				bool handle_event					|
//	+---------------------------------------------------+
bool PauseState::handle_event(const sf::Event& event) {
	if (event.key.code == sf::Keyboard::BackSpace) {
		request_state_clear();
		request_stack_push(States::Menu);
	}
	return false;
}