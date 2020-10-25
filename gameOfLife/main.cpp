#include <SFML/GRAPHICS.hpp>
#include <iostream>

using namespace sf;

void createCube(int arrOfCubes[62][62]) {
    for(int i = 1; i < 61; i ++) {
        for(int j = 1; j < 61; j ++) {
            if(arrOfCubes[i][j] == 0) {
                int numberOfCubes = 0;
                if(arrOfCubes[i-1][j-1] == 1 || arrOfCubes[i-1][j-1] == 3) {numberOfCubes += 1;}
                if(arrOfCubes[i-1][j] == 1 || arrOfCubes[i-1][j] == 3) {numberOfCubes += 1;}
                if(arrOfCubes[i-1][j+1] == 1 || arrOfCubes[i-1][j+1] == 3) {numberOfCubes += 1;}
                if(arrOfCubes[i][j+1] == 1 || arrOfCubes[i][j+1] == 3) {numberOfCubes += 1;}
                if(arrOfCubes[i+1][j+1] == 1 || arrOfCubes[i+1][j+1] == 3) {numberOfCubes += 1;}
                if(arrOfCubes[i+1][j] == 1 || arrOfCubes[i+1][j] == 3) {numberOfCubes += 1;}
                if(arrOfCubes[i+1][j-1] == 1 || arrOfCubes[i+1][j-1] == 3) {numberOfCubes += 1;}
                if(arrOfCubes[i][j-1] == 1 || arrOfCubes[i][j-1] == 3) {numberOfCubes += 1;}
                if(numberOfCubes == 3) {
                    arrOfCubes[i][j] = 2;
                }
            }
            }
        }
        for(int i = 1; i < 61; i ++) {
            for(int j = 1; j < 61; j ++) {
                if(arrOfCubes[i][j] == 3){
                    arrOfCubes[i][j] = 0;
                }
        }
    }
}

void isCellAlive(int arrOfCubes[62][62]) {
    for(int i = 1; i < 61; i ++) {
        for(int j = 1; j < 61; j ++) {
            if(arrOfCubes[i][j] == 1 || arrOfCubes[i][j] == 2) {
                int numberOfCubes = 0;
                if(arrOfCubes[i-1][j-1] == 1 || arrOfCubes[i-1][j-1] == 2 || arrOfCubes[i-1][j-1] == 3) {numberOfCubes += 1;}
                if(arrOfCubes[i-1][j] == 1  || arrOfCubes[i-1][j] == 2 || arrOfCubes[i-1][j] == 3) {numberOfCubes += 1;}
                if(arrOfCubes[i-1][j+1] == 1 || arrOfCubes[i-1][j+1] == 2 || arrOfCubes[i-1][j+1] == 3) {numberOfCubes += 1;}
                if(arrOfCubes[i][j+1] == 1 || arrOfCubes[i][j+1] == 2 || arrOfCubes[i][j+1] == 3) {numberOfCubes += 1;}
                if(arrOfCubes[i+1][j+1] == 1 || arrOfCubes[i+1][j+1] == 2 || arrOfCubes[i+1][j+1] == 3) {numberOfCubes += 1;}
                if(arrOfCubes[i+1][j] == 1 || arrOfCubes[i+1][j] == 2 || arrOfCubes[i+1][j] == 3) {numberOfCubes += 1;}
                if(arrOfCubes[i+1][j-1] == 1 || arrOfCubes[i+1][j-1] == 2 || arrOfCubes[i+1][j-1] == 3) {numberOfCubes += 1;}
                if(arrOfCubes[i][j-1] == 1 || arrOfCubes[i][j-1] == 2 || arrOfCubes[i][j-1] == 3) {numberOfCubes += 1;}

                if(numberOfCubes != 2 && numberOfCubes != 3) {
                    arrOfCubes[i][j] = 3;
                }
            }

        }
    }
    for(int i = 1; i < 61; i ++) {
        for(int j = 1; j < 61; j ++) {
            if(arrOfCubes[i][j] == 2) {
                arrOfCubes[i][j] = 1;
            }
        }
    }
}

void drawLines(RenderWindow& window) {
    for(int i = 10; i < 600; i += 10) {
        RectangleShape rect1, rect2;
        rect1.setPosition({i, 0});
        rect1.setSize({2, 600});
        rect1.setFillColor({Color::Black});

        rect2.setPosition({0, i});
        rect2.setSize({600, 2});
        rect2.setFillColor({Color::Black});

        window.draw(rect1);
        window.draw(rect2);
    }
}

int main() {
    RenderWindow window({600, 600}, "GameOFLife");
    int arrOfcubes[62][62] = {0}; // we will use arr 60x60, but our functions require more
    // 0 - dead cell, 1 - old cell, 2 - new cell, 3 - dead cell

    bool start = true;

    Clock clock;
    Time timer;
    float delay = 0.1;

    while(window.isOpen()) {
        timer += clock.getElapsedTime();
        clock.restart();
        Event event;
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            }
            if(Mouse::isButtonPressed(Mouse::Left)) {
                int y = Mouse::getPosition(window).y / 10;
                int x = Mouse::getPosition(window).x / 10;
                if(x > - 1 && x < 60 && y > -1 && y < 60){
                    arrOfcubes[y + 1][x + 1] = 2;
                }
            }
            if(event.type == Event::KeyPressed) {
                if(event.key.code == Keyboard::Space) {
                    start = false;
                }
            }
        }
        if(timer.asSeconds() >= delay && !start) {
            timer = Time::Zero;
            isCellAlive(arrOfcubes);
            createCube(arrOfcubes);
        }
        window.clear({123, 159, 198});

        drawLines(window);

        for(int i = 1; i < 61; i ++) {
            for(int j = 1; j < 61; j ++) {
                if(arrOfcubes[i][j] == 1 || arrOfcubes[i][j] == 2) {
                    RectangleShape rect;
                    rect.setFillColor(Color::Black);
                    rect.setSize({10, 10});
                    rect.setPosition({j * 10 - 10, i * 10 - 10});
                    window.draw(rect);
                }
            }
        }
        window.display();
    }
}
