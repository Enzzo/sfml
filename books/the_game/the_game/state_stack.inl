#include <cassert>

#include "state_stack.h"

//--------------------------------------------------+
//				class StateStack					|
//--------------------------------------------------+
//				void handle_event					|
//--------------------------------------------------+
void StateStack::handle_event(const sf::Event& event) {
	for (auto itr = _stack.rbegin(); itr != _stack.rend(); ++itr) {
		if (!(*itr)->handle_event(event)) {
			return;
		}
	}
	apply_pending_changes();
};

//--------------------------------------------------+
//				class StateStack					|
//--------------------------------------------------+
//			State::ptr create_state					|
//--------------------------------------------------+
State::ptr StateStack::create_state(States::ID state_id) {
	auto found = _factories.find(state_id);
	assert(found != _factories.end());

	return found->second();
};

//--------------------------------------------------+
//				class StateStack					|
//--------------------------------------------------+
//			void apply_pending_changes				|
//--------------------------------------------------+
void StateStack::apply_pending_changes() {
	for (const PendingChange& change : _pending_list) {
		switch (change.action) {
		case push:
			_stack.push_back(create_state(change.state_id));
			break;

		case pop:
			_stack.pop_back();
			break;

		case clear:
			_stack.clear();
			break;
		}
	}
	_pending_list.clear();
};