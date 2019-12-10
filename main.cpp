#include "Stopwatch.h"
#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

//TODO: Add Gtest?
// TODO Fix the Stop Watch

std::shared_ptr<Stopwatch> Stopwatch::instance = nullptr;

int main()
{
        std::shared_ptr<Stopwatch> s = Stopwatch::getInstance();
        float accumulatedTimeSinceLastUpdate = 0;


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

                // Calculate the delta
                float timeSinceLastFrame = s->getElapsedTime();
                s->restart();
                accumulatedTimeSinceLastUpdate += timeSinceLastFrame;


                if (accumulatedTimeSinceLastUpdate >= 1) {
                        std::cout << accumulatedTimeSinceLastUpdate << std::endl;
                        accumulatedTimeSinceLastUpdate -= 1;

                        // Update
                        circle.move(sf::Vector2f(10,10));
                }

                window.draw(circle);
                // draw objects here
                window.display();




        }

        return 0;
}