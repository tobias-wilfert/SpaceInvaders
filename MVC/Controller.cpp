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
                // Check that move is legal -> The player doesn't move from the screen
                if (model->pplayer->position.x - 0.05 >= -3){
                        // Move the player left
                        model->pplayer->position.x -= 0.05;
                }


        }else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
                // Check that move is legal
                if (model->pplayer->position.x + 0.05 <= (3-model->pplayer->size.width)) {
                        // Move the player right
                        model->pplayer->position.x += 0.05;
                }

        }else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
                // Keep track of the time so that the player can't spam shoot
                // Let the player shoot
        }
}
si::mvc::Controller::Controller(std::shared_ptr<Model>  model) : model(std::move(model)) {}

void si::mvc::Controller::handleTitleScreenInput(sf::RenderWindow& window) const
{
        // Check if the player presses a key
        sf::Event event{};
        while (window.pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                        window.close();
                        break;
                case sf::Event::KeyPressed:
                        model->interacted = true;
                default:
                        break;
                }
        }

}
