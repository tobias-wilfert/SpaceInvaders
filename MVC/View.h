//============================================================================
// Name        : View.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_VIEW_H
#define SPACEINVADERS_VIEW_H

#include "Model.h"

#include "../Singleton/Transformation.h"

#include <tuple>
#include <string>
#include <memory>
#include <utility>
#include <iostream>
#include <SFML/Graphics.hpp>

/// Namespace of SpaceInvaders
namespace si {

/// Namespace of Model View Controller
namespace mvc {

/**
 * The View of the MVC
 */
class View
{
public:
        View(std::shared_ptr<Model>  model, std::shared_ptr<singleton::Transformation>  transformation);

        /**
         * Main function to draw the Model
         * @param window
         */
        void display(sf::RenderWindow& window ) const;

        /**
         *
         * @param window
         */
        void displayTitleScreen(sf::RenderWindow& window ) const;

        /**
         * Fonts and Sprites are hard wired so no parameters needed
         * Throws Error if resources can't be found
         */
        void initializerResources();

        /**
         *
         * @param path
         * @return
         */
        sf::Texture loadFromFile(std::string path) const;


private:

        // Needs the model to display
        std::shared_ptr<Model> model;

        // Used to transform from the [-4,4]x[-3, 3] logic of the Model
        // to the [0,windowHeight]x[0,windowWidth] logic of the view
        std::shared_ptr<singleton::Transformation> transformation;

        /// Font that will be used throughout the game
        sf::Font font;

        /// Texture of the Player
        sf::Texture playerTexture;

        /// Textures of the Aliens
        std::tuple<sf::Texture,sf::Texture> alienA;
        std::tuple<sf::Texture,sf::Texture> alienB;
        std::tuple<sf::Texture,sf::Texture> alienC;
};

}
}

#endif // SPACEINVADERS_VIEW_H
