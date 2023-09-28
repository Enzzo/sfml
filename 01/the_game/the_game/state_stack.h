#pragma once

#include <functional>
#include <map>
#include <vector>

#include "SFML/Graphics.hpp"

#include "state_identifiers.h"
#include "state.h"

//--------------------------------------------------+
//				class StateStack					|
//--------------------------------------------------+
class StateStack : private sf::NonCopyable {
public:
	enum Action {
		push,
		pop,
		clear
	};

public:
	explicit	StateStack(State::Context context) : _context(context) {};

	template<typename T>
	void		register_state(States::ID state_id);

	void		update(sf::Time dt);
	void		draw();
	void		handle_event(const sf::Event& event);

	void		push_state(States::ID stateID);
	void		pop_state();
	void		clear_states();

	bool		is_empty()const;

private:
	State::ptr	create_state(States::ID state_id);
	void		apply_pending_changes();

private:
	struct PendingChange {
		// ...
		Action		action;
		States::ID	state_id;
	};

private:
	std::vector<State::ptr>		_stack;
	std::vector<PendingChange>	_pending_list;
	State::Context				_context;
	std::map<States::ID, std::function<State::ptr()>> _factories;
};

//--------------------------------------------------+
//				class StateStack					|
//--------------------------------------------------+
//			void register_state						|
//--------------------------------------------------+
template<typename T>
void StateStack::register_state(States::ID state_id) {
	_factories[state_id] = [this]() {
		return State::ptr(new T(*this, _context));
	};
};