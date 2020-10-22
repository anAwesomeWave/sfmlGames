#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<iostream>


using namespace sf;

void client();
void server();

void drawCircle(RenderWindow& window, int x, int y, Color color) {
    CircleShape circle;
    circle.setFillColor(color);
    circle.setRadius(10);
    circle.setPosition({x, y});
    window.draw(circle);
}

int main() {
    UdpSocket socket;
    socket.setBlocking(false);

    char connectionType;
    std::cout << "Enter 'c' for client and 's' for server: ";
    std::cin >> connectionType;
    if(connectionType == 'c') {
        client();
    } else if(connectionType == 's'){
        server();
    } else {
        std::cout << "Incorrect input - " << connectionType;
        return 0;
    }

}
