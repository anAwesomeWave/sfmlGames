#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "snakeClass.hpp"
#include "fruit.hpp"
#include "settings.hpp"
using namespace sf;

void menu(RenderWindow& window, int& level);

int main()
{
    RenderWindow window({SCR_WIDTH, SCR_HEIGHT}, "Shhhh.");

    int score = 0;
    int level;
    float delay = 0.1;

    SoundBuffer buffer1;
    buffer1.loadFromFile(EATING_SOUND);
    Sound eatSound;
    eatSound.setBuffer(buffer1);

    SoundBuffer buffer2;
    buffer2.loadFromFile(DYING_SOUND);
    Sound dieSound;
    dieSound.setBuffer(buffer2);

    Font font;
    font.loadFromFile(FONT2);
    Text txtScore, txtMenu, txtReplay;
    txtScore.setFont(font);
    txtScore.setPosition({20, 20});
    txtScore.setCharacterSize(16);
    txtScore.setString("Score: " + std::to_string(score));

    txtReplay.setFont(font);
    txtReplay.setCharacterSize(16);
    txtReplay.setPosition({SCR_WIDTH - 150, 20});
    txtReplay.setString("  Press R\nto replay.");

    txtMenu.setFont(font);
    txtMenu.setCharacterSize(16);
    txtMenu.setPosition({SCR_WIDTH - 200, SCR_HEIGHT - 60});
    txtMenu.setString("\tPress ESC\nto exit in menu.");


    Snake snake;
    Clock clock;
    float timer;
    Fruit fruit;

    menu(window, level);

    while(window.isOpen()) {

    if(snake.wasInMenu) {
        if(level < 3) {delay = 0.2;} else {delay = 0.15;}
        snake.newGame(score);
        snake.wasInMenu = false;
    }

    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    timer += time;

    Event event;
    while(window.pollEvent(event)) {
        if(event.type == Event::Closed){
            window.close();
        }
        if(event.type == Event::KeyPressed) {
            if(event.key.code == Keyboard::Escape) {
                menu(window, level);
                snake.newGame(score);
                if(level < 3) {delay = 0.1;} else {delay = 0.15;}
            }
            if(event.key.code == Keyboard::R) {
                snake.newGame(score);
                fruit.createNewFruit(window);
            }
            if(event.key.code == Keyboard::A) {
                snake.handlingInput(event.key.code);
            }
            if(event.key.code == Keyboard::W) {
                snake.handlingInput(event.key.code);
            }
            if(event.key.code == Keyboard::D) {
                snake.handlingInput(event.key.code);
            }
            if(event.key.code == Keyboard::S) {
                snake.handlingInput(event.key.code);
            }
        }
    }
    ///collision with apple///
    if(fruit.checkCollision(snake.getCoordsOfTheHead()[0], snake.getCoordsOfTheHead()[1])) {
        eatSound.play();
        snake.createNewChuck();
        fruit.setLive(false);
        if(level == 1)
            score += 100;
        if(level == 2){
            score += 150;
            delay -= 0.00005;
        }
        if(level == 3) {
            score += 200;
            delay -= 0.0001;
        }
    }

    ///collision with itself///
    if(snake.checkCollision()) {
        dieSound.play();
        snake.isLive = false;
    }
    ///collision with fruit///
    if(!fruit.getLive()) {
        fruit.createNewFruit(window);
        fruit.setLive(true);
    }
    if(!snake.isLive) {
        snake.endOfTheGame(window, score, level);
    }

    txtScore.setString("Score: " + std::to_string(score));
    window.clear();
    if(timer > delay) {
        timer = 0;
        snake.update();
        snake.turn();
    }
    window.draw(txtScore);
    window.draw(txtReplay);
    window.draw(txtMenu);
    fruit.draw(window);
    snake.draw(window);
    window.display();
    }
    return 0;
}
