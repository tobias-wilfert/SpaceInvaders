//============================================================================
// Name        : main.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Stopwatch.h"
#include "Transformation.h"

#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>

// TODO: Think about if Google tests are worth it

std::shared_ptr<Stopwatch> Stopwatch::instance = nullptr;
std::shared_ptr<Transformation> Transformation::instance = nullptr;


int main()
{
        std::shared_ptr<Stopwatch> s = Stopwatch::getInstance();
        std::shared_ptr<Transformation> t = Transformation::initialize(180,180);

        std::cout << t->convertWidthCoordinate(-1) << std::endl;



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

                        case sf::Event::Resized:
                                // Handle resize and feed it to the simulation
                                // Udpate to the transformation libary
                                window.getSize();
                                std::cout << window.getSize().y << std::endl;
                                break;
                        }
                }
                // update the game
                window.clear();

                // Calculate the delta
                float timeSinceLastFrame = s->getElapsedTime();
                s->restart();
                accumulatedTimeSinceLastUpdate += timeSinceLastFrame;

                // Update every Second
                if (accumulatedTimeSinceLastUpdate >= 1) {
                        std::cout << accumulatedTimeSinceLastUpdate << std::endl;
                        accumulatedTimeSinceLastUpdate -= 1;

                        // Update
                        circle.move(sf::Vector2f(10,10));
                }

                // Draw consitently
                window.draw(circle);
                // draw objects here
                window.display();

        }

        return 0;
}