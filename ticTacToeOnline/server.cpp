#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include "settings.hpp"

using namespace sf;

void isWin(bool& isServerWin, int mapOfTheGame[3][3]) {
    if((mapOfTheGame[0][0] == 1 && mapOfTheGame[0][1] == 1 && mapOfTheGame[0][2]) ||
       (mapOfTheGame[1][0] == 1 && mapOfTheGame[1][1] == 1 && mapOfTheGame[1][2]) ||
       (mapOfTheGame[2][0] == 1 && mapOfTheGame[2][1] == 1 && mapOfTheGame[2][2]) ||
       (mapOfTheGame[0][0] == 1 && mapOfTheGame[1][0] == 1 && mapOfTheGame[2][0]) ||
       (mapOfTheGame[0][1] == 1 && mapOfTheGame[1][1] == 1 && mapOfTheGame[2][1]) ||
       (mapOfTheGame[0][2] == 1 && mapOfTheGame[1][2] == 1 && mapOfTheGame[2][2]) ||
       (mapOfTheGame[0][0] == 1 && mapOfTheGame[1][1] == 1 && mapOfTheGame[2][2]) ||
       (mapOfTheGame[0][2] == 1 && mapOfTheGame[1][1] == 1 && mapOfTheGame[2][0])) {
        isServerWin = true;

    }
}

void drawMap(RenderWindow& window) {
    for(int i = 200; i < SCR_WIDTH; i += 200) {
            RectangleShape rect1, rect2;
            rect1.setFillColor({0, 0, 0});
            rect1.setSize({2, SCR_HEIGHT});
            rect1.setPosition({i, 0});

            rect2.setFillColor({0, 0, 0});
            rect2.setSize({SCR_WIDTH, 2});
            rect2.setPosition({0, i});
            window.draw(rect1);
            window.draw(rect2);
    }
}

void drawCircle(int x, int y, std::vector<std::pair<int, int>>& balls, int mapOfTheGame[3][3], int& turn, int& sendX, int& sendY) {
    if(x < 0 || y < 0) return;
    if(mapOfTheGame[y / 200][x / 200] == 1 || mapOfTheGame[y / 200][x / 200] == 2){
        sendX = -1;
        sendY = -1;
        return;
    }
    if(x < 200) {
        if(y < 200) {
            balls.push_back({50, 50});
        } else if(y < 400) {
            balls.push_back({50, 250});
        } else {
            balls.push_back({50, 450});
        }
    } else if(x < 400) {
        if(y < 200) {
            balls.push_back({250, 50});
        } else if(y < 400) {
            balls.push_back({250, 250});
        } else {
            balls.push_back({250, 450});
        }
    } else {
        if(y < 200) {
            balls.push_back({450, 50});
        } else if(y < 400) {
            balls.push_back({450, 250});
        } else {
            balls.push_back({450, 450});
        }
    }
    mapOfTheGame[y / 200][x / 200] = 1;
    sendX = x; sendY = y;
    turn = 1;
}

void drawSquare(int x, int y, std::vector<std::pair<int, int>>& squares) {
    if(x < 0 || y < 0) return;
    if(x < 200) {
        if(y < 200) {
            squares.push_back({50, 50});
        } else if(y < 400) {
            squares.push_back({50, 250});
        } else {
            squares.push_back({50, 450});
        }
    } else if(x < 400) {
        if(y < 200) {
            squares.push_back({250, 50});
        } else if(y < 400) {
            squares.push_back({250, 250});
        } else {
            squares.push_back({250, 450});
        }
    } else {
        if(y < 200) {
            squares.push_back({450, 50});
        } else if(y < 400) {
            squares.push_back({450, 250});
        } else {
            squares.push_back({450, 450});
        }
    }

}


void server()
{
    sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "TicTacToeServer");
    int turn = 0; // 0 - server, 1 - client
    int mapOfTheGame[3][3] = {0};

    std::vector<std::pair<int, int>> balls;
    std::vector<std::pair<int, int>> squares;
    Texture texture1, texture2;
    texture1.loadFromFile(O_TEXTURE);
    texture2.loadFromFile(X_TEXTURE);

    UdpSocket socket;
    socket.bind(55001);
    socket.setBlocking(false);

    Clock clock;
    Time timer;

    int sendX = -1; int sendY = -1;
    bool isServerWin = false;
    bool isClientWin = false;

    while (window.isOpen()){
        timer += clock.getElapsedTime();
        clock.restart();
        sf::Event event;
        window.clear(Color::White);
        Packet packet;
        timer += clock.getElapsedTime();
        clock.restart();
        ///END_OF_THE_GAME///
        if(isServerWin || isClientWin) {
            while(window.isOpen()) {
                Font font;
                font.loadFromFile(FONT);
                Text text;
                text.setFont(font);
                text.setFillColor(Color::Blue);
                text.setPosition({200, 200});
                if(isClientWin) {
                    text.setString("Client win!");
                } else {
                    text.setString("Server win!");
                }
                Event e;
                while(window.pollEvent(e)) {
                    if(e.type == Event::Closed) {
                        window.close();
                    }
                }
                window.clear(Color::White);
                window.draw(text);
                window.display();
                }
            }
        while (window.pollEvent(event)){
            if (event.type == Event::Closed) {
                window.close();
            }
            if(event.type == Event::MouseButtonPressed) {
                if(event.key.code == Mouse::Left && turn == 0 && !isServerWin && !isClientWin) {
                    drawCircle(Mouse::getPosition(window).x, Mouse::getPosition(window).y, balls, mapOfTheGame, turn, sendX, sendY);
                    isWin(isServerWin, mapOfTheGame);
                    if(timer.asSeconds() >= DELAY) {
                        timer = Time::Zero;
                        packet << sendX << sendY << turn << isServerWin;
                        socket.send(packet, "127.0.0.1", 55002);
                        packet.clear();
                    }
                }
            }
        }

        ///RECEIVE///
        IpAddress senderIp;
        unsigned short senderPort;

        if(socket.receive(packet, senderIp, senderPort) == Socket::Status::Done) {
            int senderX, senderY;
            packet >> senderX >> senderY >> turn >> isClientWin;
            mapOfTheGame[senderY / 200][senderX / 200] = 2;
            drawSquare(senderX, senderY, squares);
        }

        for(auto i : balls) {
            Sprite s;
            s.setTexture(texture1);
            s.setPosition({i.first, i.second});
            window.draw(s);
        }
        for(auto i : squares) {
            Sprite s;
            s.setTexture(texture2);
            s.setPosition({i.first, i.second});
            window.draw(s);
        }
        drawMap(window);
        window.display();
    }
}
