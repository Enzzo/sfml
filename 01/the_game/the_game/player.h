#pragma once
#include <map>

#include "SFML/Graphics.hpp"

#include "command_queue.h"
#include "entity.h"

//--------------------------------------------------+
//					class Player					|
//--------------------------------------------------+
class Player{
public:
	enum Action {
		move_left,
		move_right,
		move_up,
		move_down,
		pause,
		escape
	};

public:
	Player();

	void handle_event(const sf::Event& event, CommandQueue& commands);
	void handle_realtime_input(CommandQueue& commands);

	void assign_key(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key get_assigned_key(Action action) const;

	//TODO: �� ������� +
	void setTexture(sf::Texture) {};
	//TODO: �� ������� +
	void setPosition(float x, float y) {};
	//TODO: �� ������� +
	void move(sf::Vector2f) {};


private:
	static bool	is_realtime_action(Action action);

private:
	// TODO: ���
	float _player_speed = 30.f;

	std::map<sf::Keyboard::Key, Action> _key_binding;
	std::map<Action, Command>			_action_binding;
};