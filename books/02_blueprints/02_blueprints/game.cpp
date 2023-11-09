#include "game.h"

void game::run(int frame_per_seconds) {
	sf::Clock clock;
	sf::Time time_since_last_update = sf::Time::Zero;
	sf::Time time_per_frame = sf::seconds(1.f / frame_per_seconds);

	while (_window.isOpen()) {
		proccess_events();
		bool repaint = false;

		time_since_last_update += clock.restart();
		while (time_since_last_update > time_per_frame) {
			time_since_last_update -= time_per_frame;
			repaint = true;
			update(time_per_frame);
		}
		if (repaint) {
			render();
		}
	}
}