#include "Engine.h"

void Engine::input() {
	Event event;

	while (this->game->window.pollEvent(event)) {
		switch (event.type) {
		case Event::Closed: {
			this->game->window.close();
			break;
		}
		case Event::KeyPressed:
			if (event.key.code == Keyboard::Escape) {
				this->game->window.close();
				break;
			}
			// Spaceholder if we plan to add more screens.
			if (event.key.code == Keyboard::Space) {
				cout << "loaded" << endl;
				break;
			}
		case Event::MouseButtonPressed: {
			if (event.mouseButton.button == Mouse::Left) {
				cout << "Left mouse button was pressed" << endl;
				cout << "mouse x: " << event.mouseButton.x << endl;
				cout << "mouse y: " << event.mouseButton.y << endl;
			}
			break;
		}
									  break;
		}
			default: break;
	}
}

void Engine::run() {
	Clock clock;
}