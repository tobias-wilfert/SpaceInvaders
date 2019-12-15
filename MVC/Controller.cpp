//============================================================================
// Name        : Controller.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Controller.h"

void si::mvc::Controller::handleInput(sf::RenderWindow& window) const
{
        // Handle all events
        sf::Event event{};

        while (window.pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                        window.close();
                        break;
                        // Place to add extra Handles if needed.
                default:
                        break;
                }
        }

        // Handle game input
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
                // Move the player left

        }else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
                // Move the player right
        }else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
                // Let the player shoot
        }
}
