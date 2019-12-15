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
                while(!interacted){
                        titleScreen(window);

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
        height  = sf::VideoMode::getDesktopMode().height*0.75;
        width = height/8.f*6.f;

        // Initialize transformation and stopwatch
        stopwatch = si::singleton::Stopwatch::getInstance();
        transformation = si::singleton::Transformation::initialize(width,height);
}
void si::Game::titleScreen(sf::RenderWindow& window)
{
        sf::Font font;
        if (!font.loadFromFile("../resources/fonts/KenPixel.ttf"))
        {
                std::cout << "Error loading file" << std::endl;
                system("pause");
                // TODO Error Handling
        }

        sf::Text title("Space Invaders",font,50);
        sf::Rect<float> size = title.getGlobalBounds();
        title.setPosition(window.getSize().x/2.f-size.width/2.f,window.getSize().y/2.f-size.height/2.f);

        window.clear();
        window.draw(title);
        window.display();

        // Check if the player presses a key
        sf::Event event{};
        while (window.pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                        window.close();
                        break;
                case sf::Event::KeyPressed:
                        interacted = true;
                        // Set the clock 0 so that you don't get an illiegla bost
                        stopwatch->restart();
                default:
                        break;
                }
        }
}
