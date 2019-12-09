#include "Stopwatch.h"
#include <iostream>
#include <SFML/Graphics.hpp>

#include <memory>

std::shared_ptr<Stopwatch> Stopwatch::instance = nullptr;

int main()
{
        std::shared_ptr<Stopwatch> s = Stopwatch::getInstance();
        int i = 1;


        sf::RenderWindow window( sf::VideoMode(640,480), "Test Version");

        sf::CircleShape circle(65);

        while (window.isOpen()) {
                sf::Event event{};

                // handle all events
                while (window.pollEvent(event)) {
                        switch (event.type) {
                        case sf::Event::Closed:
                                window.close();
                                break;
                        }
                }
                // update the game
                window.clear();

                window.draw(circle);
                // draw objects here
                window.display();


                if (s->getElapsedTime() > i) {
                        std::cout << i << std::endl;
                        std::cout << s->getElapsedTime() << std::endl;
                        ++i;
                        circle.move(sf::Vector2f(10,10));
                }

        }

        return 0;
}