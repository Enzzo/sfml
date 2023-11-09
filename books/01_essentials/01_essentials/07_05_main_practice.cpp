#include <iostream>

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#define TILE_SIZE 40.f

int main() {

	// Establish a connection
	sf::TcpSocket socket;
	std::string console_input;
	std::cin >> console_input;
	
	if (console_input == "host") {
		sf::TcpListener listener;
		listener.listen(45000);
		std::cout << "Waiting for connection..." << std::endl;
		
		if (listener.accept(socket) != sf::Socket::Done) {
			return -1;
		}
	}

	else {
		std::cout << "Trying to connect..." << std::endl;
		
		//Timeout is set to 10 seconds. If nothing happens - Abort		
		if (socket.connect(console_input, 45000, sf::seconds(10)) != sf::Socket::Done) {
			// couldn't connect for some reason. Abort
			return -1;
		}
	}

	// setup the scene
	sf::RenderWindow window(sf::VideoMode(640, 480), "Networking");
	socket.setBlocking(false);

	sf::Vector2f shape_size(TILE_SIZE, TILE_SIZE);
	sf::RectangleShape local_shape(shape_size);
	sf::RectangleShape remote_shape(shape_size);

	while (window.isOpen()) {
		sf::Vector2i move_dir;
		sf::Event event;

		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::KeyPressed: {
				if (event.key.code == sf::Keyboard::W) {
					move_dir.y += -1;
				}
				else if (event.key.code == sf::Keyboard::A) {
					move_dir.x += -1;
				}
				else if (event.key.code == sf::Keyboard::S) {
					move_dir.y += 1;
				}
				else if (event.key.code == sf::Keyboard::D) {
					move_dir.x += 1;
				}
				break;
			}
			case sf::Event::Closed: {
				window.close();
				break;
			}
			}

			// check for new packets
			sf::Packet packet;
			if (socket.receive(packet) == sf::Socket::Done) {
				sf::Vector2f pos;
				packet >> pos.x >> pos.y;
				remote_shape.setPosition(pos);
			}

			// update frame
			if (move_dir.x != 0 || move_dir.y != 0) {
				local_shape.move(move_dir.x * TILE_SIZE, move_dir.y * TILE_SIZE);
				sf::Packet packet;
				packet << local_shape.getPosition().x << local_shape.getPosition().y;
				
				if (socket.send(packet) != sf::Socket::Done) {
					// handle problem (probably the other disconnected
					return -1;
				}
			}
		}

		window.clear();

		window.draw(local_shape);
		window.draw(remote_shape);

		window.display();
	}

	return 0;
}