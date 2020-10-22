#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "settings.hpp"
#include "fruit.hpp"

Fruit::Fruit() {
    srand(time(NULL));
    x = rand() % (SCR_WIDTH - int(size) * 2);
    y = rand() % (SCR_HEIGHT - int(size) * 2);
    if(x <=0)
        x += 20;
    if(y <= 0)
        y += 20;
    if(x >= SCR_WIDTH)
        x -= 20;
    if(y >= SCR_HEIGHT)
        y -= 20;
    texture.loadFromFile(APPLE);
    sprite.setTexture(texture);
    sprite.setScale({sizeX, sizeY});
    sprite.setPosition({x, y});
    isLive = true;
}

bool Fruit::getLive(){
    return isLive;
}

void Fruit::setLive(bool live){
    isLive = live;
}

void Fruit::createNewFruit(sf::RenderWindow& window) {
    x = rand() % SCR_WIDTH - 10;
    y = rand() % SCR_HEIGHT - 10;
    sprite.setPosition({x, y});
}

void Fruit::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

std::vector<float> Fruit::getCoords(){
    return {x, y};
}

bool Fruit::checkCollision(float X, float Y) {
    sf::IntRect fruit(x, y, size, size);
    if(fruit.contains(X, Y) || fruit.contains(X + 5, Y + 5) || fruit.contains(X + 10, Y + 10))
        return true;
    return false;

}
