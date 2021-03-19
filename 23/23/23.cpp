#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "AssetManager.h"

int main()try{

    sf::RenderWindow window(sf::VideoMode(640, 480), "Title");
    AssetManager manager;

    sf::Sprite player(manager.SetTexture("myTexture1.png"));
    sf::Sprite player2(manager.SetTexture("myTexture2.png"));
    sf::Sprite player3(manager.SetTexture("myTexture1.png"));

    player.setPosition(10, 10);
    player.setOrigin(16, 16);
    //player.setTextureRect(sf::IntRect(0, 0, 32, 32));

    player2.setPosition(40, 40);
    player2.setOrigin(16, 16);
    //player2.setTextureRect(sf::IntRect(0, 0, 32, 32));

    player3.setPosition(80, 80);
    player3.setOrigin(16, 16);
    //player3.setTextureRect(sf::IntRect(0, 0, 32, 32));

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::milliseconds delta;
    int total_time = 0;

    while (window.isOpen()) {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        delta = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

        if (delta.count() >= 10) {
            begin = end;
            std::cout<<++total_time<<" sec\n";
            player2.rotate(1);
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.key.code == sf::Keyboard::Key::Escape)
                window.close();
        }
        window.clear();
        window.draw(player);
        window.draw(player2);
        window.draw(player3);
        window.display();
    }

    return 0;
}
catch (FailedTexture f) {
    std::cerr << f.What();
}
catch (std::exception e) {
    std::cerr << e.what();
}