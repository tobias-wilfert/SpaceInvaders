//============================================================================
// Name        : View.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "View.h"

si::mvc::View::View(std::shared_ptr<Model>  model,
    std::shared_ptr<singleton::Transformation>  transformation)
    : model(std::move(model)), transformation(std::move(transformation))
{
        // TODO Handel error and if needed Destruct View
        initializerResources();
}

void si::mvc::View::display(sf::RenderWindow& window) const
{
        // Clear the window
        // This causes MVC to be not a clean as in Swift as we need to re draw everything even when it didn't change.
        window.clear();

        // Draw all the entities
        // Do cast if extra info is needed

        // Draw the player test
        sf::RectangleShape rect(sf::Vector2f(transformation->convertWidth(model->pplayer->size.width),
            transformation->convertHeight(model->pplayer->size.height)));

        rect.setPosition(transformation->convertXCoordinate(model->pplayer->position.x)
            ,transformation->convertYCoordinate(model->pplayer->position.y));

        //rect.setTexture(&playerTexture);
        rect.setTexture(&playerTexture);
        window.draw(rect);

        // Display the new updated interface to the user
        window.display();
}

void si::mvc::View::displayTitleScreen(sf::RenderWindow& window) const
{
        // TODO: Add extra info the title screen
        sf::Text title("Space Invaders",font,50);
        sf::Rect<float> size = title.getGlobalBounds();
        title.setPosition(window.getSize().x/2.f-size.width/2.f,window.getSize().y/2.f-size.height/2.f);

        window.clear();
        window.draw(title);
        window.display();
}

void si::mvc::View::initializerResources()
{

        // Load the Font that will be used
        if (!font.loadFromFile("../resources/fonts/KenPixel.ttf"))
        {
                std::cout << "Error loading file" << std::endl;
                system("pause");
                // TODO Error Handling
        }

        // Load the Textures that will be used
        // PLayer
        playerTexture = loadFromFile("../resources/img/player.png");

        // Alien A
        alienA = std::make_tuple(loadFromFile("../resources/img/alien-a1.png"),
            loadFromFile("../resources/img/alien-a2.png"));

        // Alien B
        alienB = std::make_tuple(loadFromFile("../resources/img/alien-b1.png"),
            loadFromFile("../resources/img/alien-b2.png"));

        // Alien C
        alienC = std::make_tuple(loadFromFile("../resources/img/alien-c1.png"),
            loadFromFile("../resources/img/alien-c2.png"));

}

sf::Texture si::mvc::View::loadFromFile(std::string path) const
{
        sf::Texture texture;

        if(!texture.loadFromFile(path))
        {
                std::cout << "Load failed:"<< path << std::endl;
                system("pause");
                // TODO Error Handling
        }

        return texture;
}
