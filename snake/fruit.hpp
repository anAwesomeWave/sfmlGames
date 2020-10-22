#ifndef FRUIT_HPP_INCLUDED
#define FRUIT_HPP_INCLUDED

class Fruit{
private:
    float x;
    float y;
    int size = 10;
    float sizeX = 0.025;
    float sizeY = 0.025;
    bool isLive;
    sf::Texture texture;
    sf::Sprite sprite;
public:
    Fruit();
    void draw(sf::RenderWindow& window);
    bool getLive();
    void setLive(bool live);
    void createNewFruit(sf::RenderWindow& window);
    bool checkCollision(float X, float Y);
    std::vector<float> getCoords();

};
#endif // FRUIT_HPP_INCLUDED
