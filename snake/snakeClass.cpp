#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "snakeClass.hpp"
#include "settings.hpp"

void menu(sf::RenderWindow& window, int& level);

Snake::Snake() : isLive(true), wasInMenu(false){
    randomCoords();
}
void Snake::randomCoords() {
    srand(time(NULL));
    posOfChuck head = {rand() % SCR_WIDTH - 10, rand() % SCR_HEIGHT - 10};
    numberOfChucks.push_back(head);
    posOfChuck firstChuck {head.x + 10, head.y};
    numberOfChucks.push_back(firstChuck);
}

void Snake::draw(sf::RenderWindow& window) {
    for(int i = 0; i < numberOfChucks.size(); i ++) {
        sf::RectangleShape rect;
        rect.setSize({size, size});
        rect.setFillColor(sf::Color::Green);
        if(i == 0) {
            rect.setFillColor(sf::Color::Yellow);
        }
        rect.setPosition({numberOfChucks[i].x, numberOfChucks[i].y});
        window.draw(rect);
    }

}
void Snake::createNewChuck() {
    posOfChuck newChuck = numberOfChucks[numberOfChucks.size() - 1];
    if(dir == 1) { // left
        newChuck.x += size;
    }
    if(dir == 2) { // up
        newChuck.y += size;
    }
    if(dir == 3) { // right
        newChuck.x -= size;
    }
    if(dir == 4) { // down
        newChuck.y -= size;
    }
    numberOfChucks.push_back(newChuck);
}

void Snake::handlingInput(sf::Keyboard::Key key) {
    if(key == sf::Keyboard::A && dir != 3) {
        dir = 1;
    }
    if(key == sf::Keyboard::W && dir != 4) {
        dir = 2;
    }
    if(key == sf::Keyboard::D && dir != 1) {
        dir = 3;
    }
    if(key == sf::Keyboard::S && dir != 2) {
        dir = 4;
    }

}

void Snake::turn() {
    if(dir == 1)
        numberOfChucks[0].x -= speed;
    if(dir == 2)
        numberOfChucks[0].y -= speed;
    if(dir == 3)
        numberOfChucks[0].x += speed;
    if(dir == 4)
        numberOfChucks[0].y += speed;

    ///teleportation///
    if(numberOfChucks[0].x < 0) {
        numberOfChucks[0].x = SCR_WIDTH;
    }
    if(numberOfChucks[0].x > SCR_WIDTH) {
        numberOfChucks[0].x = 0;
    }
    if(numberOfChucks[0].y > SCR_HEIGHT) {
        numberOfChucks[0].y = 0;
    }
    if(numberOfChucks[0].y < 0) {
        numberOfChucks[0].y = SCR_HEIGHT;
    }
}



void Snake::update() {
    if(dir){ //if snake is moving
        float lastX; float lastY; float _lastX; float _lastY;
        _lastX = numberOfChucks[0].x;
        _lastY = numberOfChucks[0].y;
        for(int i = 1; i < numberOfChucks.size(); i ++) {
            lastX = numberOfChucks[i].x;
            lastY = numberOfChucks[i].y;
            numberOfChucks[i].x = _lastX;
            numberOfChucks[i].y = _lastY;
            _lastX = lastX;
            _lastY = lastY;
        }
    }
}

std::vector<float> Snake::getCoordsOfTheHead(){
    return {numberOfChucks[0].x, numberOfChucks[0].y};
}

int Snake::getDir() {
    return dir;
}

bool Snake::checkCollision() {
    sf::IntRect head(numberOfChucks[0].x, numberOfChucks[0].y, size, size);
    for(int i = 2; i < numberOfChucks.size(); i ++) {
        if(head.contains(numberOfChucks[i].x, numberOfChucks[i].y)){
            return true;
        }
    }
    return false;
}

void Snake::endOfTheGame(sf::RenderWindow& window, int& score, int&level) {
    bool isEnd = true;
    sf::Font font;
    font.loadFromFile(FONT2);
    sf::Text text1;
    text1.setFont(font);
    text1.setCharacterSize(18);
    sf::Text replay;
    replay.setFont(font);
    replay.setCharacterSize(12);
    replay.setPosition({SCR_WIDTH - 175, SCR_HEIGHT - 50});
    replay.setString("Press R to replay.");

    std::ifstream fin;
    int lastBestScore = 0;
    fin.open("score.txt", std::ios::in);
    fin >> lastBestScore;
    fin.close();
    if(score > lastBestScore) {
        std::ofstream fout;
        fout.open("score.txt", std::ios::out);
        fout << score;
        fout.close();
    }
    if(score < 500) {
        text1.setString("Are you even trying?\n\nYour score is " + std::to_string(score));

    } else if(score < 1000) {
        text1.setString("Nice one!\n\nYour score is " + std::to_string(score));
    } else if(score < 5000) {
        text1.setString("Awesome!\n\nYour score is " + std::to_string(score));
    } else if(score < 10000) {
        text1.setString("   ...\n\nYour score is " + std::to_string(score));
    } else {
        text1.setString("   GOD\n\nYour score is " + std::to_string(score));
    }

    while(isEnd && window.isOpen()) {
        window.clear();
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::R) {
                    isEnd = false;
                    newGame(score);
                }
                if(event.key.code == sf::Keyboard::Escape) {
                    isEnd = false;
                    wasInMenu = true;
                    menu(window, level);
                }

            }
        }
        text1.setPosition({SCR_WIDTH / 2 - 150, SCR_HEIGHT / 2 - 100});
        if(score > lastBestScore) {
            sf::Text gj;
            gj.setFont(font);
            gj.setCharacterSize(15);
            gj.setString("You beat the record. GJ! \nBest score was - " + std::to_string(lastBestScore));
            gj.setPosition({0, 0});
            window.draw(gj);
        }

        window.draw(text1);
        window.draw(replay);
        window.display();
    }

}

void Snake::newGame(int& score) {
    isLive = true;
    dir = 0;
    score = 0;
    numberOfChucks.erase(numberOfChucks.begin(), numberOfChucks.end());
    randomCoords();
}
