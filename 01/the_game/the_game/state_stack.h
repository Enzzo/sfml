#pragma once

#include <functional>
#include <map>
#include <vector>

#include "SFML/Graphics.hpp"

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
	explicit	StateStack(State::Context context);

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
	State::Ptr	create_state(States::ID state_id);
	void		apply_pending_changes();

private:
	struct PendingChange {
		// ...
		Action		action;
		States::ID	state_id;
	};

private:
	std::vector<State::Ptr>		_stack;
	std::vector<PendingChange>	_pending_list;
	State::Context				_context;
	std::map<States::ID, std::function<State::Ptr()>> _factories;
};