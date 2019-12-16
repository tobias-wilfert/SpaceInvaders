//============================================================================
// Name        : Game.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Game.h"

std::shared_ptr<si::singleton::Stopwatch> si::singleton::Stopwatch::instance = nullptr;
std::shared_ptr<si::singleton::Transformation> si::singleton::Transformation::instance = nullptr;

// TODO: Push once without all the load from File to check that it works

void si::Game::execute()
{
        // Initialize the game
        initialize();
        float accumulatedTimeSinceLastUpdate = 0;

        //TODO: Model View and Controller constructor
        mvc::Model model{};
        std::shared_ptr<mvc::Model> modelPointer = std::make_shared<mvc::Model>(model);
        mvc::View view{modelPointer,transformation};
        mvc::Controller controller{modelPointer};

        // Create the window
        sf::RenderWindow window( sf::VideoMode(transformation->get_width(),transformation->get_height()), "SpaceInvaders");

        // Main game Loop
        while (window.isOpen()) {

                // Till the player interacts with the game don't start a level
                while(!modelPointer->is_interacted()){
                        controller.handleTitleScreenInput(window);
                        view.displayTitleScreen(window);
                        // Reset the stop watch
                        stopwatch->restart();
                }

                // Calculate the delta -> Clock
                float timeSinceLastFrame = stopwatch->getElapsedTime();
                stopwatch->restart();
                accumulatedTimeSinceLastUpdate += timeSinceLastFrame;

                // Update every X Second -> Clock
                if (accumulatedTimeSinceLastUpdate >= 0.01) {

                        // TODO: Do something with the model
                        controller.handleInput(window);

                        // Reset the delta
                        accumulatedTimeSinceLastUpdate -= 0.01;
                }

                // View should be updated every frame
                view.display(window);

        }
}

void si::Game::initialize()
{
        // Get the size of the monitor
        unsigned int width{0}, height{0};
        height = sf::VideoMode::getDesktopMode().height * 0.75;
        width = height / 8.f * 6.f;

        // Initialize transformation and stopwatch
        stopwatch = si::singleton::Stopwatch::getInstance();
        transformation = si::singleton::Transformation::initialize(width, height);
}
