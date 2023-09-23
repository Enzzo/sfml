#include <iostream>

#include "player.h"
#include "aircraft.h"

//--------------------------------------------------+
//					class Player					|
//--------------------------------------------------+
//					Constructor						|
//--------------------------------------------------+
Player::Player() {
	_key_binding[sf::Keyboard::Left] = move_left;
	_key_binding[sf::Keyboard::Right] = move_right;

	_action_binding[move_left].action = [](SceneNode& node, sf::Time dt) {
		// node.move(-player_speed * dt.asSeconds(), 0.f);
		node.move(-30 * dt.asSeconds(), 0.f);
	};

	_action_binding[move_right].action = [](SceneNode& node, sf::Time dt) {
		// node.move(player_speed * dt.asSeconds(), 0.f);
		node.move(30 * dt.asSeconds(), 0.f);
	};

	for (auto [key, action] : _action_binding) {
		action.category = Category::PlayerAircraft;
	}
}

//--------------------------------------------------+
//					class Player					|
//--------------------------------------------------+
//					void handle_event				|
//--------------------------------------------------+
void Player::handle_event(	const sf::Event& event,
							CommandQueue& commands) {
	if (event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::P) {
		Command output;
		output.category = Category::PlayerAircraft;
		output.action = [](SceneNode& s, sf::Time) {
			std::cout << s.getPosition().x << ","
				<< s.getPosition().y << "\n";
		};
		commands.push(output);
	}
}

//--------------------------------------------------+
//					class Player					|
//--------------------------------------------------+
//			void handle_realtime_input				|
//--------------------------------------------------+
void Player::handle_realtime_input(CommandQueue& commands) {

	for (auto& [key, action] : _key_binding) {
		if (sf::Keyboard::isKeyPressed(key) &&
			is_realtime_action(action)) {
			commands.push(_action_binding[action]);
		}
	}

	/*const float player_speed = 30.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		Command move_left;
		move_left.category = Category::PlayerAircraft;
		move_left.action = derived_action<Aircraft>(AircraftMover(-player_speed, 0.f));
		commands.push(move_left);
	}*/
};

//--------------------------------------------------+
//					class Player					|
//--------------------------------------------------+
//					void assign_key					|
//--------------------------------------------------+
void Player::assign_key(Action action, sf::Keyboard::Key key) {
	auto binding = std::find_if(_key_binding.begin(), _key_binding.end(), [action](const auto bnd) {
		return bnd.second == action;
		});
	
	if (binding != _key_binding.end()) {
		if (binding->first != key) {
			_key_binding.erase(binding->first);
		}
	}
	_key_binding[key] = action;
}

//--------------------------------------------------+
//					class Player					|
//--------------------------------------------------+
//		sf::Keyboard::Key get_assigned_key			|
//--------------------------------------------------+
sf::Keyboard::Key Player::get_assigned_key(Action action) const {
	auto binding = std::find_if(_key_binding.begin(), _key_binding.end(), [action](const auto& bnd) {
		return bnd.second == action;
		});
	return binding->first;
}

//--------------------------------------------------+
//					class Player					|
//--------------------------------------------------+
//				bool is_realtime_action				|
//--------------------------------------------------+

bool Player::is_realtime_action(Action action) {
	// TODO: заглушка
	return false;
}