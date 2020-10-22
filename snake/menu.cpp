#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "settings.hpp"


void choseLevel(sf::RenderWindow& window, int& level , bool& isMenu) {

    sf::Texture leftButtonText;
    leftButtonText.loadFromFile(LEFT_BUTTON1);

    sf::Sprite leftButtonSpr;
    leftButtonSpr.setTexture(leftButtonText);
    leftButtonSpr.setScale({0.097, 0.097});

    sf::Font font;
    font.loadFromFile(FONT2);

    sf::Text level1, level2, level3;
    level1.setFont(font);
    level1.setString("\tLevel 1\nSpeed equal to 1\nGet 100 points per fruit");
    level1.setCharacterSize(14);
    level1.setPosition({35, 50});

    level2.setFont(font);
    level2.setString("\tLevel 2\nSpeed equal to 1 \n+ 0.1 every 2 fruit\nGet 150 points per fruit");
    level2.setCharacterSize(14);
    level2.setPosition({310, 50});

    level3.setFont(font);
    level3.setString("\tLevel 3\nSpeed equal to 1.5\n+0.1 every 1 fruit\nGet 200 points per fruit");
    level3.setCharacterSize(14);
    level3.setPosition({35, 150});

    bool isLevel = true;
    int levelType = 0;

    while(window.isOpen() && isLevel) {
        level1.setFillColor({255, 255, 255});
        level2.setFillColor({255, 255, 255});
        level3.setFillColor({255, 255, 255});

        if(sf::IntRect(0, 0, 50, 50).contains(sf::Mouse::getPosition(window))) {levelType = 1;}
        if(sf::IntRect(35, 50, 253, 50).contains(sf::Mouse::getPosition(window))) {levelType = 2; level1.setFillColor({120, 0, 0});}
        if(sf::IntRect(310, 50, 253, 50).contains(sf::Mouse::getPosition(window))) {levelType = 3; level2.setFillColor({120, 0, 0});}
        if(sf::IntRect(35, 150, 253, 50).contains(sf::Mouse::getPosition(window))) {levelType = 4; level3.setFillColor({120, 0, 0});}

        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if(levelType == 1) {isLevel = false;}
                if(levelType == 2) {isMenu = false; isLevel = false; level = 1;}
                if(levelType == 3) {isMenu = false; isLevel = false; level = 2;}
                if(levelType == 4) {isMenu = false; isLevel = false; level = 3;}
            }
        }
        levelType = 0;
        window.clear({0, 222, 145});
        window.draw(leftButtonSpr);
        window.draw(level1);
        window.draw(level2);
        window.draw(level3);
        window.display();
    }
}


void menu(sf::RenderWindow& window, int& level) {

    sf::Music music;
    music.openFromFile(MENU_MUSIC);
    music.play();

    sf::Font font;
    font.loadFromFile(FONT2);
    sf::Text playButton, texturesButton, exitButton, title;
    playButton.setFont(font);
    playButton.setPosition({0, 120});
    playButton.setCharacterSize(16);
    playButton.setString("Play");
    texturesButton.setFont(font);
    texturesButton.setPosition({0, 200});
    texturesButton.setCharacterSize(16);
    texturesButton.setString("Choose texture");
    exitButton.setFont(font);
    exitButton.setPosition({0, 280});
    exitButton.setCharacterSize(16);
    exitButton.setString("Exit");
    title.setFont(font);
    title.setPosition({240, 50});
    title.setCharacterSize(20);
    title.setFillColor(sf::Color::Green);
    title.setString("Snake!");

    int menuNum = 0;
    bool isMenu = true;

    while(window.isOpen() && isMenu) {
        playButton.setFillColor({255, 255, 255});
        texturesButton.setFillColor({255, 255, 255});
        exitButton.setFillColor({255, 255, 255});

        if(sf::IntRect(0, 120, 65, 20).contains(sf::Mouse::getPosition(window))) {
            playButton.setFillColor({0, 120, 230}),
            menuNum = 1;
         }
        if(sf::IntRect(0, 200, 188, 20).contains(sf::Mouse::getPosition(window))) {
            texturesButton.setFillColor({0, 120, 230}),
            menuNum = 2;
         }
        if(sf::IntRect(0, 280, 50, 20).contains(sf::Mouse::getPosition(window))) {
            exitButton.setFillColor({0, 120, 230}),
            menuNum = 3;
         }

        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if(menuNum == 1) {
                    choseLevel(window, level, isMenu);
                }
                if(menuNum == 2) {}
                if(menuNum == 3) {
                    isMenu = false;
                    window.close();
                }
            }
        }
        menuNum = 0;
        window.clear();
        window.draw(playButton);
        window.draw(texturesButton);
        window.draw(exitButton);
        window.draw(title);
        window.display();
    }
}

