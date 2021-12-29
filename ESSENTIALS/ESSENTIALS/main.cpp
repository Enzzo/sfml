#include <iostream>
#include <chrono>

#include <SFML/Graphics.hpp>

#include "AssetManager.h"
#include "Animation.h"

int main() {

	AssetManager am;

	sf::RenderWindow window(sf::VideoMode(640, 480), "Title");
	window.setFramerateLimit(60);

	const sf::Vector2u &w_size = window.getSize();
	sf::View view(sf::FloatRect(0, 0, w_size.x, w_size.y));
	window.setView(view);

	sf::Vector2i spriteSize(32, 32);
	sf::Sprite sprite;
	sprite.setPosition()
	Animator animator(sprite);

	//Create an animation and get the reference to it
	auto& idleAnimation = animator.CreateAnimation("Idle", "sprites\\gem_blue.png", sf::seconds(1), true);
	idleAnimation.AddFrames(sf::Vector2i(0, 0), spriteSize, 8);
	
	auto& idleAnimationShort = animator.CreateAnimation("IdleShort", "sprites\\gem_blue.png", sf::seconds(.5f), true);
	idleAnimationShort.AddFrames(sf::Vector2i(0, 0), spriteSize, 8);

	auto& idleAnimationSmall = animator.CreateAnimation("IdleSmall", "sprites\\gem_blue.png", sf::seconds(1.5f), true);
	idleAnimationSmall.AddFrames(sf::Vector2i(32, 0), spriteSize, 3);
	idleAnimationSmall.AddFrames(sf::Vector2i(64, 0), spriteSize, 2);

	auto& idleAnimationOnce = animator.CreateAnimation("IdleOnce", "sprites\\gem_blue.png", sf::seconds(.5f), false);
	idleAnimationOnce.AddFrames(sf::Vector2i(0, 0), spriteSize, 8);

	sf::Clock clock;
	while (window.isOpen()) {
		
		sf::Time deltaTime = clock.restart();
		animator.Update(deltaTime);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}

				if (event.key.code == sf::Keyboard::Key::A) {
					animator.SwitchAnimation("Idle");
					std::cerr.flush();
					std::cerr << "\rIdle";
				}
				else if (event.key.code == sf::Keyboard::Key::S) {
					animator.SwitchAnimation("IdleShort");
					std::cerr.flush();
					std::cerr << "\rIdleShort";
				}
				else if (event.key.code == sf::Keyboard::Key::D) {
					animator.SwitchAnimation("IdleSmall");
					std::cerr.flush();
					std::cerr << "\rIdleSmall";
				}
				else if (event.key.code == sf::Keyboard::Key::F) {
					animator.SwitchAnimation("IdleOnce");
					std::cerr.flush(); 
					std::cerr << "\rIdleOnce";
				}
			}
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}