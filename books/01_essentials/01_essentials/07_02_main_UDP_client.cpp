#include <iostream>

#include <SFML/Network.hpp>

int main0702c() {

	sf::UdpSocket udp_socket;

	// send some data to the other client
	const int msg_size = 100;
	char message[msg_size] = "Nice that you have there";

	if (udp_socket.send(message, msg_size, "localhost", 45000) != sf::Socket::Done) {
		// something wrong - data not sent
		std::cerr << "something wrong\n";
	}

	system("pause");

	return 0;
}