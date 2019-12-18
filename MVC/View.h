//============================================================================
// Name        : View.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_VIEW_H
#define SPACEINVADERS_VIEW_H

#include "Model.h"
#include "../Singleton/Transformation.h"

#include <array>
#include <memory>
#include <string>
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
        View(std::shared_ptr<Model> model, std::shared_ptr<singleton::Transformation> transformation);

        /**
         \n Main function of View
         \n @param window The sfml window the users sees and interacts with
         */
        void display(sf::RenderWindow& window) const;

        /**
         \n Displays the title Screen
         \n @param window The sfml window the users sees and interacts with
         */
        void displayTitleScreen(sf::RenderWindow& window) const;

private:
        // --- Data members ---

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
        std::array<sf::Texture,2> alienA;
        std::array<sf::Texture,2> alienB;
        std::array<sf::Texture,2> alienC;
        std::array<sf::Texture,2> alienM;

        // --- Functions ---

        /**
         \n Loads Font and Texture from file for the View to use
         \n @warning If any of the textures can't be loaded the Program exit
         */
        void initializerResources();

        /**
         \n Loads Texture from file
         \n @throw runtime_error("Failed to allocate resources at: "+path);
         \n @param path The path to the file that should contain the Texture
         \n @return The texture that file contained
         */
        sf::Texture loadFromFile(std::string path) const;

        /**
         \n Finds out what derived class entity is an entity of,
         \n casts and delegates further to the correct function to draw the entity
         \n @param entity The entity that should be drawn
         \n @param window The window the users sees
         */
        void drawEntity(const std::shared_ptr<si::entity::Entity>& entity, sf::RenderWindow& window) const;

        /**
         \n Draws an instance of Counter to the Window
         \n @param counter The counter that should be drawn
         \n @param window The window the users sees
         */
        void drawCounter(const std::shared_ptr<si::entity::Counter>& counter, sf::RenderWindow& window) const;

        /**
         \n Draws an instance of Player to the Window
         \n @param player The player that should be drawn
         \n @param window The window the users sees
         */
        void drawPlayer(const std::shared_ptr<si::entity::Player>& player, sf::RenderWindow& window) const;

        /**
         *
         * @param player
         * @param window
         */
        void drawEnemy(const std::shared_ptr<si::entity::Enemy>& enemy, sf::RenderWindow& window) const;

        /**
         *
         * @param colour
         * @return
         */
        sf::Color gameColourToSFMLColour(const entity::colourType colour) const;

        /**
         \n Creates a RectangleShape representing entity
         \n @param entity The entity that will be used to specify the proportions of the RectangleShape
         \n @return An instance of sf::RectangleShape with dimensions and position of Entity
         */
        sf::RectangleShape entityToRectangle(const std::shared_ptr<si::entity::Entity>& entity) const;
};

} // namespace mvc
} // namespace si

#endif // SPACEINVADERS_VIEW_H
