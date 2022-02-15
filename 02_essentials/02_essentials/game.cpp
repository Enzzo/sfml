#include "game.h"
#include "source_manager.h"

Game::Game() :window_(sf::VideoMode(640, 480), "SFML Application")
			, mTextures()
			, mPlayer()
			, mTimePerFrame(sf::seconds(1.f / 60.f))
			, mPlayerSpeed(500) {
	
	mTextures.Load(Textures::ID::Eagle, "Media\\Textures\\Eagle.png");

	mPlayer.setTexture(mTextures.Get(Textures::ID::Eagle));
	sf::FloatRect bounds = mPlayer.getLocalBounds();
	mPlayer.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	mPlayer.setPosition(100.f, 100.f);	
}

void Game::Run() {

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen()) {
		//ProcessEvents();
		timeSinceLastUpdate += clock.restart();
		
		while (timeSinceLastUpdate > mTimePerFrame) {
			timeSinceLastUpdate -= mTimePerFrame;
			ProcessEvents();
			Update(mTimePerFrame);
		}
		
		Render();
	}
}

void Game::ProcessEvents() {
	sf::Event event;
	while (window_.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::EventType::KeyPressed: {
			HandlePlayerInterrupt(event.key.code, true);
			break;
		}
		case sf::Event::EventType::KeyReleased: {
			HandlePlayerInterrupt(event.key.code, false);
			break;
		}
		case sf::Event::Closed: {
			window_.close();
			break;
		}
		}
	}
}

void Game::Update(const sf::Time deltaTime) {
	sf::Vector2f movement(0.f, 0.f);

	if (is_moving_up && mPlayer.getPosition().y > 0)
		movement.y -= mPlayerSpeed;
	if (is_moving_down && mPlayer.getPosition().y < window_.getSize().y)
		movement.y += mPlayerSpeed;
	if (is_moving_left && mPlayer.getPosition(). x > 0)
		movement.x -= mPlayerSpeed;
	if (is_moving_right && mPlayer.getPosition().x < window_.getSize().x)
		movement.x += mPlayerSpeed;

	mPlayer.move(movement * deltaTime.asSeconds());
}

void Game::Render() {
	window_.clear();
	window_.draw(mPlayer);
	window_.display();
}

void Game::HandlePlayerInterrupt(const sf::Keyboard::Key key, const bool is_pressed) {
	if (key == sf::Keyboard::Key::W) {
		is_moving_up = is_pressed;
	}
	if (key == sf::Keyboard::Key::S) {
		is_moving_down = is_pressed;
	}
	if (key == sf::Keyboard::Key::A) {
		is_moving_left = is_pressed;
	}
	if (key == sf::Keyboard::Key::D) {
		is_moving_right = is_pressed;
	}
}