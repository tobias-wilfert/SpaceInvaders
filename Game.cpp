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
        // Create the window
        sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(transformation->get_width()),
                                              static_cast<unsigned int>(transformation->get_height())),
                                "SpaceInvaders");
        // Main game Loop
        while (window.isOpen()) {

                // Till the player interacts with the game don't start a level
                while (!modelPtr->is_interacted()) {
                        controller.handleTitleScreenInput(window);
                        view.displayTitleScreen(window);
                        stopwatch->restart(); // Reset the stop watch
                }

                // Display the game over screen if the player has lost
                while (modelPtr->is_game_over()) {
                        view.displayGameOverScreen(window);
                        controller.handleGameEndScreenInput(window);
                }

                // Display the won screen if the player has lost
                while (modelPtr->is_game_won()) {
                        view.displayWonScreen(window);
                        controller.handleGameEndScreenInput(window);
                }

                // Update every X Second
                if (stopwatch->getElapsedTime() >= 1.f / cyclesPerSecond) {
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

si::Game::Game(float cycles_per_second, const std::deque<std::string>& files)
    : modelPtr{std::make_shared<mvc::Model>(mvc::Model{})}, view{}, controller{cycles_per_second, modelPtr},
      cyclesPerSecond(cycles_per_second), stopwatch{si::singleton::Stopwatch::getInstance()}
{
        // Get the size of the monitor
        double width{0}, height{0};
        height = sf::VideoMode::getDesktopMode().height * 0.75;
        width = height / 8 * 6;
        // Initialize transformation
        transformation = si::singleton::Transformation::initialize(static_cast<int>(width), static_cast<int>(height));

        view = mvc::View{modelPtr, transformation};

        // Parse the input files
        Parser parser{};
        std::deque<std::shared_ptr<mvc::Level>> levels;
        for (const std::string& file : files) {
                levels.push_back(parser.parseFile(file));
        }
        modelPtr->set_levels(levels);
}
