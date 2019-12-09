#include "Stopwatch.h"
#include <iostream>
#include <SFML/Graphics.hpp>


Stopwatch* Stopwatch::instance = nullptr;

int main()
{
        sf::RenderWindow window( sf::VideoMode(640,480), "Test Version");

        while (window.isOpen()) {
                sf::Event event;

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

                // draw objects here
                window.display();
        }

        std::cout << CLOCKS_PER_SEC << std::endl;

        // Stopwatch *s = s->getInstance();
        // Superior
        Stopwatch* s = Stopwatch::getInstance();

        std::cout << s->getElapsedTime() << std::endl;

        int i = 1;
        while (i < 5) {
                if (s->getElapsedTime() > i) {
                        std::cout << i << std::endl;
                        std::cout << s->getElapsedTime() << std::endl;
                        ++i;
                }
                if (i == 4) {
                        s->restart();
                        i++;
                }
        }

        return 0;
}