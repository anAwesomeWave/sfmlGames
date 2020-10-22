#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "settings.h"

using namespace sf;

int grid[12][12];
int sgrid[12][12];

void newGame() {
    for(int i = 1; i <= 10; i ++) {
        for(int j = 1; j <= 10; j ++) {
            if(rand() % 10 == 0) {grid[i][j] = 9;} else {grid[i][j] = 0;}
        }
    }
    int n = 0;
    for(int i = 1; i <= 10; i ++) {
        for(int j = 1; j <= 10; j ++) {
            if(grid[i][j] == 9) continue;
            if(grid[i - 1][j - 1] == 9) n++;
            if(grid[i - 1][j] == 9) n++;
            if(grid[i - 1][j + 1] == 9) n++;
            if(grid[i][j + 1] == 9) n++;
            if(grid[i + 1][j + 1] == 9) n++;
            if(grid[i + 1][j] == 9) n++;
            if(grid[i + 1][j - 1] == 9) n++;
            if(grid[i][j - 1] == 9) n++;
            grid[i][j] = n;
            n = 0;
        }
    }
    for(int i = 1; i <= 10; i ++) {
        for(int j = 1; j <= 10; j ++) {
            sgrid[i][j] = 10;
        }
    }
}
int main()
{
    srand(time(NULL));
    RenderWindow window ({500, 500}, "Mines!");
    Clock clock;
    Time timer;
    int minuts = 0; int seconds = 0;
    Font font;
    font.loadFromFile(TIME_FONT);
    Text timeTxt;
    timeTxt.setFont(font);
    timeTxt.setCharacterSize(16);
    timeTxt.setPosition({235, 0});

    newGame();

    Texture t;
    t.loadFromFile(TEXTURE);
    Sprite s(t);
    while(window.isOpen()) {
        window.clear();
        timer += clock.getElapsedTime();
        clock.restart();
        seconds = timer.asSeconds();
        if(seconds  >= 60) {
            minuts = seconds / 60;
            seconds %= 60;
        }
        timeTxt.setString(std::to_string(minuts) + ":" + std::to_string(seconds));

        Vector2i pos = Mouse::getPosition(window);
        int x = pos.x / 32;
        int y = pos.y / 32;

        Event event;
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            }
            if(event.type == Event::KeyPressed) {
                if(event.key.code == Keyboard::R) {
                    newGame();
                    seconds = 0; minuts = 0; timer =sf::seconds(0.f);
                }
            }
            if(event.type == Event::MouseButtonPressed) {
                if(event.key.code == Mouse::Left) {
                    sgrid[y][x] = grid[y][x];
                }
                if(event.key.code == Mouse::Right) {
                    sgrid[y][x] = 11;
                }
            }
        }
        int gridCounter = 0;
        int sgridCounter = 0;
        for(int i = 1; i <= 10; i ++) {
            for(int j = 1; j <= 10; j ++) {
                if(sgrid[y][x] == 9) sgrid[i][j] = grid[i][j];
                if(sgrid[i][j] == 0) {
                    for(int k = i - 1; k < i + 2; k++) {
                        for(int l = j- 1; l < j + 2; l ++) {
                            sgrid[k][l] = grid[k][l];
                        }
                    }
                }
                if(grid[i][j] == 9) {
                    gridCounter ++;
                }
                if(sgrid[i][j] == 10) {
                    sgridCounter ++;
                }

                s.setTextureRect({sgrid[i][j] * 32, 0, 32, 32});
                s.setPosition({j * 32, i * 32});
                window.draw(s);
            }
        }
        if(gridCounter == sgridCounter) {
            std::cout << 1;
            newGame();
        }
        window.draw(timeTxt);
        window.display();
    }
    return 0;
}
