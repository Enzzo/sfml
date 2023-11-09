#include <iostream>

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

int main0703() {

	sf::RenderWindow window(sf::VideoMode(800, 600), "Non blocking sockets", sf::Style::Default);

	sf::UdpSocket socket;

	// bind the socket to a port so it can receive data
	socket.bind(45000);
	socket.setBlocking(false);

	while (window.isOpen()) {
		// receive the data
		const std::size_t size = 100;
		char data[size];
		std::size_t read_size;
		sf::IpAddress sender_ip;
		unsigned short remote_port;
		auto status = socket.receive(data, size, read_size, sender_ip, remote_port);

		// check to see if anyone has tried to send us any data
		if (status == sf::Socket::Done) {
			// do something with the data
		}
		else {
			// no data available
		}

		// Input + Updata + Render here
	}

	return 0;
}