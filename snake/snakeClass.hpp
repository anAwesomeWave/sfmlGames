#ifndef SNAKECLASS_HPP_INCLUDED
#define SNAKECLASS_HPP_INCLUDED

class Snake {
private:
    struct posOfChuck {
        float x;
        float y;
    };
    std::vector<posOfChuck> numberOfChucks;
    int dir = 0;
    float size = 10;
    float speed = 10;
public:
    bool isLive;
    bool wasInMenu;
public:
    Snake();
    void draw(sf::RenderWindow& window);
    void turn();
    void createNewChuck();
    void handlingInput(sf::Keyboard::Key key);
    void update();
    std::vector<float> getCoordsOfTheHead();
    int getDir();
    bool checkCollision();
    void endOfTheGame(sf::RenderWindow& window, int& score, int& level);
    void newGame(int& score);
    void randomCoords();

};


#endif // SNAKECLASS_HPP_INCLUDED
