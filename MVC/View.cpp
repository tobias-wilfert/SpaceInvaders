//============================================================================
// Name        : View.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "View.h"
void si::mvc::View::display(sf::RenderWindow& window) const
{
        // Clear the window
        // This causes MVC to be not a clean as in Swift as we need to re draw everything even when it didn't change.
        window.clear();

        // Draw all the entities
        // Do cast if extra info is needed
        //window.draw(rect);
        //window.draw(text);

        // Draw the player test

        sf::RectangleShape rect(sf::Vector2f(transformation->convertWidth(model->pplayer->size.width),
            transformation->convertHeight(model->pplayer->size.height)));

        rect.setPosition(transformation->convertXCoordinate(model->pplayer->position.x)
            ,transformation->convertYCoordinate(model->pplayer->position.y));

        // Load the texture -> View DO THIS IN AN INITIAL FILE
        sf::Texture texture;
        if(!texture.loadFromFile("../resources/img/player.png"))
        {
                std::cout << "Load failed" << std::endl;
                system("pause");
        }
        rect.setTexture(&texture);
        window.draw(rect);


        // Display the new updated interface to the user
        window.display();
}
si::mvc::View::View(const std::shared_ptr<Model>& model,
                    const std::shared_ptr<singleton::Transformation>& transformation)
    : model(model), transformation(transformation)
{
}
