#pragma once
#include <string>
#include <vector>
#include <list>

#include <SFML/Graphics.hpp>

#include "AssetManager.h"

class Animator {
	struct Animation;
	Animator::Animation* FindAnimation(const std::string& name);
	void SwitchAnimation(Animator::Animation* animation);

	sf::Sprite& m_Sprite;
	sf::Time m_CurrentTime;
	std::list<Animator::Animation> m_Animations;
	Animator::Animation* m_CurrentAnimation;

public:
	struct Animation {
		std::string m_Name;
		std::string m_TextureName;
		std::vector<sf::IntRect> m_Frames;
		sf::Time m_Duration;
		bool m_Looping;

		Animation(const std::string& name, const std::string& textureName, const sf::Time& duration, bool looping)
			: m_Name(name)
			, m_TextureName(textureName)
			, m_Duration(duration)
			, m_Looping(looping) {}

		void AddFrames(const sf::Vector2i& startFrom, const sf::Vector2i& frameSize, unsigned int frames) {
			sf::Vector2i current = startFrom;
			for (unsigned int i = 0; i < frames; ++i) {
				m_Frames.push_back(sf::IntRect(current.x, current.y, frameSize.x, frameSize.y));
				current.x += frameSize.x;
			}
		}
	};

	Animator(sf::Sprite& sprite);

	Animator::Animation& CreateAnimation(const std::string& name, const std::string& textureName, const sf::Time& duration, bool loop = false);

	void Update(const sf::Time& dt);

	bool SwitchAnimation(const std::string& name);

	std::string GetCurrentAnimationName() const;
};