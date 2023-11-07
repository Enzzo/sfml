#pragma once
#include <memory>

#include "state_stack.h"
#include "state_identifiers.h"
#include "source_manager.h"
#include "player.h"
#include "world.h"

//	+---------------------------------------------------+
//	|				class State							|
//	+---------------------------------------------------+
class State {
public:
	typedef std::unique_ptr<State> ptr;
	struct Context {
		Context(sf::RenderWindow& window,
			TextureHolder& textures,
			FontHolder& fonts,
			Player& player);

		sf::RenderWindow* window;
		TextureHolder* textures;
		FontHolder* fonts;
		Player* player;
	};

public:
	State(StateStack& stack, Context context) : _stack(&stack), _context(context) {};
	virtual			~State();
	
	virtual void	draw() = 0;
	virtual bool	update(sf::Time dt) = 0;
	virtual bool	handle_event(const sf::Event& event) = 0;

protected:
	void			request_stack_push(States::ID state_id);
	void			request_stack_pop();
	void			request_state_clear();

	Context			get_context() const;

private:
	StateStack*		_stack;
	Context			_context;
};

//	+---------------------------------------------------+
//	|				class TitleState					|
//	+---------------------------------------------------+
class TitleState : public State {
public:
	TitleState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time);
	virtual bool handle_event(const sf::Event& event);

public:
	sf::Sprite	_background_sprite;
	sf::Text	_text;

	bool		_show_text;
	sf::Time	_text_effect_time;
};

//	+---------------------------------------------------+
//	|				class MenuState						|
//	+---------------------------------------------------+
class MenuState : public State {
public:
	MenuState(StateStack& stack, Context context);

	void update_option_text();
	void handle_event(sf::Event);

private:
	enum OptionNames {
		Play,
		Exit,
	};

private:
	std::vector<sf::Text>	_options;
	std::size_t				_option_index;
};

//	+---------------------------------------------------+
//	|				class GameState						|
//	+---------------------------------------------------+
class GameState : public State {
public:
	GameState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time);
	virtual bool handle_event(const sf::Event& event);

private:
	World	_world;
	Player& _player;
};

//	+---------------------------------------------------+
//	|				class PauseState					|
//	+---------------------------------------------------+
class PauseState : public State {
public:
	virtual void draw();
	virtual bool update(sf::Time);
	virtual bool handle_event(const sf::Event& event);

private:
	sf::Text _paused_text;
	sf::Text _instruction_text;
};