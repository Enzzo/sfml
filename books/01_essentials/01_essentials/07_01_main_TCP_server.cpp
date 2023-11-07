#include <iostream>

#include <SFML/Network.hpp>

int main() {

	// start listening for incoming sockets
	sf::TcpListener listener;

	listener.listen(45000);

	// what until the listener has accepted a valid connection
	sf::TcpSocket socket;
	if (listener.accept(socket) != sf::Socket::Done) {
		return -1;
	}

	sf::sleep(sf::seconds(1));

	// read the data
	const std::size_t size = 100;
	char data[size];
	std::size_t read_size;
	if (socket.receive(data, size, read_size) != sf::Socket::Done) {
		// something went wrong - data was not received
		return -1;
	}

	std::cout << data << std::endl;

	return 0;
}