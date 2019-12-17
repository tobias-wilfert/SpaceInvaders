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
         \n Main function of View
         \n @param window The sfml window the users sees and interacts with
         */
        void display(sf::RenderWindow& window ) const;

        /**
         \n Displays the title Screen
         \n @param window The sfml window the users sees and interacts with
         */
        void displayTitleScreen(sf::RenderWindow& window ) const;


        //TODO: Complete
        /**
         \n Loads Font and Texture from file for the View to use
         \n @throw
         */
        void initializerResources();

        /**
         \n Loads Texture from file
         \n @throw
         \n @param path The path to the file that should conain the Texture
         \n @return The texture that file contained
         */
        sf::Texture loadFromFile(std::string path) const;


private:

        /// Needs the model to display
        std::shared_ptr<Model> model;

        /**
         \n Used to transform from the [-4,4]x[-3, 3] logic of the Model
         \n to the [0,windowHeight]x[0,windowWidth] logic of the view
         */

        std::shared_ptr<singleton::Transformation> transformation;

        /// Font that will be used throughout the game
        sf::Font font;

        /// Texture of the Player
        sf::Texture playerTexture;

        /// Textures of the Aliens
        std::tuple<sf::Texture,sf::Texture> alienA;
        std::tuple<sf::Texture,sf::Texture> alienB;
        std::tuple<sf::Texture,sf::Texture> alienC;
        std::tuple<sf::Texture,sf::Texture> alienM;


        /**
         *
         * @param entity
         * @param window
         */
        void drawEntity(const std::shared_ptr<si::entity::Entity>& entity, sf::RenderWindow& window) const;

        /**
         *
         * @param entity
         * @param window
         */
        void drawCounter(const std::shared_ptr<si::entity::Entity>& entity, sf::RenderWindow& window) const;

        /**
         *
         * @param entity
         * @param window
         */
        void drawPlayer(const std::shared_ptr<si::entity::Entity>& entity, sf::RenderWindow& window) const;

        /**
         *
         * @param entity
         * @return
         */
        sf::RectangleShape entityToRectangle( const std::shared_ptr<si::entity::Entity>& entity) const;


};

}
}

#endif // SPACEINVADERS_VIEW_H
