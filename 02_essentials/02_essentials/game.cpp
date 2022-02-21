#include "game.h"

Game::Game() :mWindow(sf::VideoMode(640, 480), "SFML Application")
			, mWorld(mWindow)
			, mFont()
			, mStatisticsText()
			, mStatisticsUpdateTime()
			, mStatisticsNumFrames(0){
	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
}

void Game::run() {

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen()) {
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents() {
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::KeyPressed: {
			handlePlayerInterrupt(event.key.code, true);
			break;
		}
		case sf::Event::KeyReleased: {
			handlePlayerInterrupt(event.key.code, false);
			break;
		}
		case sf::Event::Closed: {
			mWindow.close();
			break;
		}
		}
	}
}

void Game::update(const sf::Time elapsedTime) {
	mWorld.update(elapsedTime);
}

void Game::render() {
	mWindow.clear();
	mWorld.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);
	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime) {
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f)) {
		mStatisticsText.setString(
			"Frames / Second = " + std::to_string(mStatisticsNumFrames) + "\n" + 
			"Time / Update = " + std::to_string(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");
		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Game::handlePlayerInterrupt(const sf::Keyboard::Key key, const bool is_pressed) {
	
}