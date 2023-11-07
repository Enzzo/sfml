#include <iostream>

#include <SFML/Network.hpp>

int main_client() {

	sf::TcpSocket tcp_socket;
	if (tcp_socket.connect("192.168.0.102", 45000) != sf::Socket::Done) {
		// connection failed;
		std::cerr << "connection failed";
		return -1;
	}

	const int msg_size = 100;
	char message[msg_size] = "Nice that you have there";

	if (tcp_socket.send(message, msg_size) != sf::Socket::Done) {
		// something went wrong - data was not sent
	}

	// send some data to the other client

	tcp_socket.disconnect();

	return 0;
}