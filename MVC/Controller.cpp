//============================================================================
// Name        : Controller.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Controller.h"

#include <utility>

si::mvc::Controller::Controller(float cycles_per_second, std::shared_ptr<Model> model,
    std::shared_ptr<singleton::Stopwatch>  stopwatch)
    : cyclesPerSecond(cycles_per_second), model(std::move(model)), stopwatch(std::move(stopwatch))
{
}

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
        float playerMovement = model->playerMovementSpeed/cyclesPerSecond;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                // Check that move is legal -> The player doesn't move from the screen
                if (model->player->position.x - playerMovement >= -3) {
                        // Move the player left
                        model->player->position.x -= playerMovement;
                }

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                // Check that move is legal
                if (model->player->position.x + playerMovement <= (3 - model->player->size.width)) {
                        // Move the player right
                        model->player->position.x += playerMovement;
                }

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                // Keep track of the time so that the player can't spam shoot
                // Check if shooting is available
                if (model->coolDownCounter->get_value() == 0) {
                        // Let the player shoot

                        // Reset the counter
                        // TODO Fine tune the value
                        model->coolDownCounter->set_value(200);
                }
        }
}

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
void si::mvc::Controller::updateModel() const
{
        // TODO: Update the movement of bullets alliens and the cooldown counter
        if (model->coolDownCounter->get_value() > 0) {
                model->coolDownCounter->set_value(model->coolDownCounter->get_value() - 1);
        }
}
