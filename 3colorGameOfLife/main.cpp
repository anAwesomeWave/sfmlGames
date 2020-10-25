#include <SFML/GRAPHICS.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace sf;

void createMapOfCells(int arrOfCubes[82][122]) {
    for(int i = 1; i < 81; i ++) {
        for(int j = 1; j < 121; j ++) {
            arrOfCubes[i][j] = rand() % 3 + 1;
        }
    }
}

void changeCell(int arrOfCubes[82][122]) {
    for(int i = 1; i < 81; i ++) {
        for(int j = 1; j < 121; j ++) {
            if(arrOfCubes[i][j] == 1) {
                int numberOfGreenCells = 0;

                if(arrOfCubes[i-1][j-1] == 3 || arrOfCubes[i-1][j-1] == 6) {numberOfGreenCells += 1;}
                if(arrOfCubes[i-1][j] == 3 || arrOfCubes[i-1][j] == 6) {numberOfGreenCells += 1;}
                if(arrOfCubes[i-1][j+1] == 3 || arrOfCubes[i-1][j+1] == 6) {numberOfGreenCells += 1;}
                if(arrOfCubes[i][j+1] == 3 || arrOfCubes[i][j+1] == 6) {numberOfGreenCells += 1;}
                if(arrOfCubes[i+1][j+1] == 3 || arrOfCubes[i+1][j+1] == 6) {numberOfGreenCells += 1;}
                if(arrOfCubes[i+1][j] == 3 || arrOfCubes[i+1][j] == 6) {numberOfGreenCells += 1;}
                if(arrOfCubes[i+1][j-1] == 3 || arrOfCubes[i+1][j-1] == 6) {numberOfGreenCells += 1;}
                if(arrOfCubes[i][j-1] == 3 || arrOfCubes[i][j-1] == 6) {numberOfGreenCells += 1;}

                if(numberOfGreenCells > 2) {
                    arrOfCubes[i][j] = 4;
                }
            }
            if(arrOfCubes[i][j] == 2) {
                int numberOfRedCells = 0;

                if(arrOfCubes[i-1][j-1] == 1 || arrOfCubes[i-1][j-1] == 4) {numberOfRedCells += 1;}
                if(arrOfCubes[i-1][j] == 1 || arrOfCubes[i-1][j] == 4) {numberOfRedCells += 1;}
                if(arrOfCubes[i-1][j+1] == 1 || arrOfCubes[i-1][j+1] == 4) {numberOfRedCells += 1;}
                if(arrOfCubes[i][j+1] == 1 | arrOfCubes[i][j+1] == 4) {numberOfRedCells += 1;}
                if(arrOfCubes[i+1][j+1] == 1 || arrOfCubes[i+1][j+1] == 4) {numberOfRedCells += 1;}
                if(arrOfCubes[i+1][j] == 1 || arrOfCubes[i+1][j] == 4) {numberOfRedCells += 1;}
                if(arrOfCubes[i+1][j-1] == 1 || arrOfCubes[i+1][j-1] == 4) {numberOfRedCells += 1;}
                if(arrOfCubes[i][j-1] == 1 || arrOfCubes[i][j-1] == 4) {numberOfRedCells += 1;}

                if(numberOfRedCells > 2) {
                    arrOfCubes[i][j] = 5;
                }
            }
            if(arrOfCubes[i][j] == 3) {
                int numberOfBlueCells = 0;

                if(arrOfCubes[i-1][j-1] == 2 || arrOfCubes[i-1][j-1] == 5) {numberOfBlueCells += 1;}
                if(arrOfCubes[i-1][j] == 2 || arrOfCubes[i-1][j] == 5) {numberOfBlueCells += 1;}
                if(arrOfCubes[i-1][j+1] == 2 || arrOfCubes[i-1][j+1] == 5) {numberOfBlueCells += 1;}
                if(arrOfCubes[i][j+1] == 2 || arrOfCubes[i][j+1] == 5) {numberOfBlueCells += 1;}
                if(arrOfCubes[i+1][j+1] == 2 || arrOfCubes[i+1][j+1] == 5) {numberOfBlueCells += 1;}
                if(arrOfCubes[i+1][j] == 2 || arrOfCubes[i+1][j] == 5) {numberOfBlueCells += 1;}
                if(arrOfCubes[i+1][j-1] == 2 || arrOfCubes[i+1][j-1] == 5) {numberOfBlueCells += 1;}
                if(arrOfCubes[i][j-1] == 2 || arrOfCubes[i][j-1] == 5) {numberOfBlueCells += 1;}

                if(numberOfBlueCells > 2) {
                    arrOfCubes[i][j] = 6;
                }
            }

        }
    }
    for(int i = 1; i < 81; i ++) {
        for(int j = 1; j < 121; j ++) {
            if(arrOfCubes[i][j] == 4)  {
                arrOfCubes[i][j] = 3;
            }
            if(arrOfCubes[i][j] == 5)  {
                arrOfCubes[i][j] = 1;
            }
            if(arrOfCubes[i][j] == 6)  {
                arrOfCubes[i][j] = 2;
            }
        }
    }

}


int main() {
    RenderWindow window({1200, 800}, "GameOFLife");
    srand(time(NULL));
    int arrOfcubes[82][122] = {0}; // we will use arr 120x80, but function require more
    createMapOfCells(arrOfcubes);

    bool start = true;

    Clock clock;
    Time timer;
    float delay = 0.01;

    while(window.isOpen()) {
        timer += clock.getElapsedTime();
        clock.restart();
        Event event;
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            }
            if(event.type == Event::KeyPressed) {
                if(event.key.code == Keyboard::Space) {
                    start = false;
                }
            }
        }
        if(timer.asSeconds() >= delay && !start) {
            timer = Time::Zero;
            changeCell(arrOfcubes);
        }
        window.clear({123, 159, 198});


        for(int i = 1; i < 81; i ++) {
            for(int j = 1; j < 121; j ++) {
                    RectangleShape rect;
                    if(arrOfcubes[i][j] == 1)
                        rect.setFillColor({212,123,145});
                    if(arrOfcubes[i][j] == 2)
                        rect.setFillColor({123,159,198});
                    if(arrOfcubes[i][j] == 3)
                        rect.setFillColor({93,76,124});
                    rect.setSize({10, 10});
                    rect.setPosition({j * 10 - 10, i * 10 - 10});
                    window.draw(rect);
            }
        }
        window.display();
    }
}
