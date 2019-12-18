//============================================================================
// Name        : Game.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Game.h"

std::shared_ptr<si::singleton::Stopwatch> si::singleton::Stopwatch::instance = nullptr;
std::shared_ptr<si::singleton::Transformation> si::singleton::Transformation::instance = nullptr;

void si::Game::execute()
{
        // Initialize the game
        initialize();

        //Model View and Controller constructor
        mvc::Level level{};
        mvc::Model model{};
        model.set_level(level);
        std::shared_ptr<mvc::Model> modelPointer = std::make_shared<mvc::Model>(model);
        mvc::View view{modelPointer, transformation};
        mvc::Controller controller{cyclesPerSecond,modelPointer,stopwatch};

        // Create the window
        sf::RenderWindow window(sf::VideoMode(transformation->get_width(), transformation->get_height()),
                                "SpaceInvaders");

        // Main game Loop
        while (window.isOpen()) {

                // Till the player interacts with the game don't start a level
                while (!modelPointer->is_interacted()) {
                        controller.handleTitleScreenInput(window);
                        view.displayTitleScreen(window);
                        stopwatch->restart(); // Reset the stop watch
                }

                // Update every X Second
                if (stopwatch->getElapsedTime() >= 1.f/cyclesPerSecond) {

                        // Update the model and handle input
                        controller.updateModel();
                        controller.handleInput(window);

                        // Reset the delta
                        stopwatch->restart();
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
si::Game::Game(float cycles_per_second) : cyclesPerSecond(cycles_per_second) {}
