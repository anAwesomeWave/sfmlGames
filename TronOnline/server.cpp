#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<iostream>


using namespace sf;

void drawCircle(RenderWindow& window, int x, int y, Color color);

void server() {
    RenderWindow window({400, 400}, "...server...");

    UdpSocket socket;
    socket.bind(55001);
    socket.setBlocking(false);

    int x = -100; int y = -100;
    float speed = 1.5;

    Clock clock;
    Time timer;
    float delay = 0.001;

    while(window.isOpen()){
        timer += clock.getElapsedTime();
        clock.restart();
        Event e;
        while(window.pollEvent(e)) {
            if(e.type == Event::Closed) {
                window.close();
            }
        }
        ///SEND///
        Packet packet;
        packet << Mouse::getPosition(window).x << Mouse::getPosition(window).y;
        if(timer.asSeconds() >= delay){
            timer = Time::Zero;
            socket.send(packet, "127.0.0.1", 55002);
        }
        packet.clear();
        ///RECEIVE///
        IpAddress senderIp;
        unsigned short senderPort;
        if(socket.receive(packet, senderIp, senderPort) == Socket::Status::Done) {
                drawCircle(window, 100, 100, {0, 255, 0});
            packet >> x >> y;
        }
        window.clear();
        drawCircle(window, x, y, {0, 255, 0});
        window.display();
    }
}
