#include "animator.h"
#include "asset_manager.h"

//	+-----------------------------------------------+
//	| class animator								|
//	+-----------------------------------------------+
//	| + constructor									|
//	+-----------------------------------------------+
animator::animator(sf::Sprite& sprite)
	:_sprite(sprite)
	, _current_time()
	, _current_animation(nullptr) {}

//	+-----------------------------------------------+
//	| class animator								|
//	+-----------------------------------------------+
//	| + animation& create_animation					|
//	+-----------------------------------------------+
animator::animation& animator::create_animation(const std::string& name, const std::string& texture_path, const sf::Time& duration, bool loop) {
	_animations.push_back(animator::animation(name, texture_path, duration, loop));

	// if we don't have any other animations, use that as current animation
	if (_current_animation == nullptr) {
		switch_animation(&_animations.back());
	}

	return _animations.back();
}

//	+-----------------------------------------------+
//	| class animator								|
//	+-----------------------------------------------+
//	| + bool switch_animation						|
//	+-----------------------------------------------+
bool animator::switch_animation(const std::string& name) {
	animator::animation* animation = find_animation(name);
	
	if (animation != nullptr) {
		switch_animation(animation);
		return true;
	}

	return false;
}

//	+-----------------------------------------------+
//	| class animator								|
//	+-----------------------------------------------+
//	| + string get_current_animator_name			|
//	+-----------------------------------------------+
std::string animator::get_current_animator_name() const {
	if (_current_animation != nullptr) {
		return _current_animation->_name;
	}

	// if no animation is playing, return empty string
	return "";
}

//	+-----------------------------------------------+
//	| class animator								|
//	+-----------------------------------------------+
//	| + void update									|
//	+-----------------------------------------------+
void animator::update(const sf::Time& dt) {
	// if we don't have any animations yet return
	if (_current_animation == nullptr) {
		return;
	}

	_current_time += dt;

	// get the current animation frame
	float scaled_time = (_current_time.asSeconds() / _current_animation->_duration.asSeconds());
	int num_frames = _current_animation->_frames.size();
	int current_frame = static_cast<int>(scaled_time * num_frames);

	// if the animation is looping, calculate the correct frame
	if (_current_animation->_looping) {
		current_frame %= num_frames;
	}
	else if (current_frame >= num_frames) {// if the current frame is greater than the number of frames
		current_frame = num_frames - 1; // show last frame
	}

	// set the texture rectangle, depending on the frame
	_sprite.setTextureRect(_current_animation->_frames.at(current_frame));
}

//	+-----------------------------------------------+
//	| class animator								|
//	+-----------------------------------------------+
//	| - animation* find_animation					|
//	+-----------------------------------------------+
animator::animation* animator::find_animation(const std::string& name) {
	for (auto& anim : _animations) {
		if (anim._name == name) {
			return &anim;
		}
	}

	return nullptr;
}

//	+-----------------------------------------------+
//	| class animator								|
//	+-----------------------------------------------+
//	| - void switch_animation						|
//	+-----------------------------------------------+
void animator::switch_animation(animator::animation* animation) {
	// change the sprite texture
	if (animation != nullptr) {
		_sprite.setTexture(asset_manager::instance()->get_texture(animation->_texture_path));
	}

	_current_animation = animation;
	_current_time = sf::Time::Zero; // reset the time
}