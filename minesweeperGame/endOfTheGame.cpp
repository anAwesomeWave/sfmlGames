#include <SFML/Graphics.hpp>
#include "settings.h"
#include <cstdlib>
#include <ctime>

void endOfTheGame(sf::RenderWindow& window, bool isWin) {
    sf::Font font;
    font.loadFromFile(FONT);
    sf::Text text;
    text.setFont(font);
    text.setPosition({150, 150});
    if(isWin) {
        text.setString("You win!");
    } else {
        text.setString("You lose!");
    }
    sf::Time timer;
    sf::Clock clock;
    srand(time(NULL));

    while(window.isOpen()) {
        sf::Event event;
        timer += clock.getElapsedTime();
        clock.restart();
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if(timer.asSeconds() > DELAY) {
            timer = sf::Time::Zero;
            text.setFillColor({30, rand() % 255, rand() % 255});
        }
        window.clear(sf::Color::Black);
        window.draw(text);
        window.display();
    }
}
