#pragma once

#include <string>
#include <vector>
#include <list>

#include <SFML/Graphics.hpp>

//	+-----------------------------------------------+
//	| class animator								|
//	+-----------------------------------------------+
class animator {
public:
	//	+-----------------------------------------------+
	//	| struct animation								|
	//	+-----------------------------------------------+
	struct animation {
		animation(const std::string& name,
			const std::string& texture_path,
			const sf::Time& duration,
			bool looping)
			: _name(name)
			, _texture_path(texture_path)
			, _duration(duration)
			, _looping(looping)
		{}

		void add_frames(const sf::Vector2i& start_from, const sf::Vector2i frame_size, unsigned int frames) {
			sf::Vector2i current = start_from;
			for (unsigned int i = 0; i < frames; ++i) {

				//	add current frame from position and frame size
				_frames.push_back(sf::IntRect(current.x, current.y, frame_size.x, frame_size.y));

				//	advance current frame horizontally
				current.x += frame_size.x;
			}
		}

		std::string _name;
		std::string _texture_path;
		std::vector<sf::IntRect> _frames;
		sf::Time _duration;
		bool _looping;	
	};

public:
	animator(sf::Sprite& sprite);

	animator::animation& create_animation(const std::string& name,
		const std::string& texture_name,
		const sf::Time& duration,
		bool loop = false);

	void update(const sf::Time& dt);

	//	returns if the switch was successful
	bool switch_animation(const std::string& name);

	std::string get_current_animator_name() const;

private:
	//	returns the animation with the passed name
	//	returns nullptr if no such animation is found
	animator::animation* find_animation(const std::string& name);

	void switch_animation(animator::animation* animation);

	//	reference to the sprite
	sf::Sprite& _sprite;
	sf::Time _current_time;
	std::list<animator::animation> _animations;
	animator::animation* _current_animation;
};