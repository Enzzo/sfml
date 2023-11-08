#include <iostream>

#include <SFML/Network.hpp>

int main0702s() {

	sf::UdpSocket socket;

	// bind the socket to a port so it can receive data
	socket.bind(45000);

	// receive the data
	const size_t size = 100;
	char data[size];
	std::size_t read_size;
	sf::IpAddress sender_ip;
	unsigned short remote_port;

	if (socket.receive(data, size, read_size, sender_ip, remote_port) != sf::Socket::Done) {
		// something went wrong - data was not received
		return -1;
	}

	std::cout << "Received data from: " << sender_ip << " on " << remote_port << std::endl;
	std::cout << data << std::endl;

	system("pause");
	return 0;
}