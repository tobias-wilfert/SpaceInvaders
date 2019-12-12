//============================================================================
// Name        : Game.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Game.h"
#include "resources.h"

std::shared_ptr<Stopwatch> Stopwatch::instance = nullptr;
std::shared_ptr<Transformation> Transformation::instance = nullptr;


void Game::execute()
{
        // This is where the real stuff happens
        // Initialize the game
        initialize();

        sf::RenderWindow window( sf::VideoMode(transformation->get_width(),transformation->get_height()), "SpaceInvaders");

        sf::Font font;
        // TODO: Could be more elegant
        std::string pathString = path;
        if (!font.loadFromFile(pathString+"fonts/KenPixel.ttf"))
        {
                std::cout << "Error loading file" << std::endl;
                system("pause");
        }
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(50);
        text.setString("Space Invaders");
        sf::Rect<float> size = text.getGlobalBounds();
        text.setPosition(window.getSize().x/2.f-size.width/2.f,window.getSize().y/2.f-size.height/2.f);

        float xw = 0.52, yh = 0.32;
        float x=0-xw/2.f, y=3.5;
        float accumulatedTimeSinceLastUpdate = 0;
        sf::RectangleShape rect(sf::Vector2f(transformation->convertWidth(xw),transformation->convertHeight(yh)));

        // Load the texture -> View
        // TODO: Adjust the Working director of the project for the resources to work
        sf::Texture texture;
        if(!texture.loadFromFile(pathString+"img/player.png"))
        {
                std::cout << "Load failed" << std::endl;
                system("pause");
        }
        rect.setTexture(&texture);


        // Main game Loop
        while (window.isOpen()) {

                // TODO: Call a level

                // TODO: Controller and Model should be in a Clock Loop to assure that every PC is equally fast

                // Call a level
                // A level has a Model, View and Controller

                // Handle all events -> Controller
                sf::Event event{};
                while (window.pollEvent(event)) {
                        switch (event.type) {
                        case sf::Event::Closed:
                                window.close();
                                break;
                                // Place to add extra Handels if needed.
                        default:
                                break;
                        }
                }
                // Update the game -> Model
                rect.setPosition(transformation->convertXCoordinate(x), transformation->convertYCoordinate(y));
                rect.setSize(sf::Vector2f(transformation->convertWidth(xw),transformation->convertHeight(yh)));

                // Calculate the delta -> Clock
                float timeSinceLastFrame = stopwatch->getElapsedTime();
                stopwatch->restart();
                accumulatedTimeSinceLastUpdate += timeSinceLastFrame;

                // Update every Second -> Clock
                if (accumulatedTimeSinceLastUpdate >= 1) {

                        accumulatedTimeSinceLastUpdate -= 1;
                        std::cout <<transformation->convertYCoordinate(y) <<":"<< y << std::endl;
                }

                // Draw Objects here -> View
                window.clear();

                // Draw consistently -> View
                window.draw(rect);
                window.draw(text);

                // Draw objects here -> View
                window.display();
        }
}

void Game::initialize()
{
        // Get the size of the monitor
        unsigned int width{0}, height{0};
        // TODO: Fine tune with the school PC
        height  = sf::VideoMode::getDesktopMode().height*0.75;
        width = height/8.f*6.f;

        // Initialize transformation and stopwatch
        stopwatch = Stopwatch::getInstance();
        transformation = Transformation::initialize(width,height);
}

