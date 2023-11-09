#include <iostream>

#include <SFML/Network.hpp>

int main0704() {

	sf::Packet packet;
	sf::Vector2f position(1.5f, 0.5f);
	sf::String name = "Enemy";
	sf::Int16 id = 1000;

	packet << id << name << position.x << position.y;

	// send data:
	sf::TcpSocket socket1;
	// connect to a listener
	
	if (socket1.send(packet) != sf::Socket::Done) {
		// something wrong
	}

	// receive data:
	sf::TcpListener listener;
	sf::TcpSocket socket;

	if (socket.receive(packet) == sf::Socket::Done) {
		// pacet received. do something
	}

	// receive the packet here
	sf::Vector2f r_position;
	sf::String r_name;
	sf::Int16 r_id;

	packet >> r_id >> r_name >> position.x >> position.y;

	return 0;
}