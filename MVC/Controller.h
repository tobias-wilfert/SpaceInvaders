//============================================================================
// Name        : Controller.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_CONTROLLER_H
#define SPACEINVADERS_CONTROLLER_H

#include "../Singleton/Stopwatch.h"
#include "Level.h"
#include "Model.h"

#include <SFML/Graphics.hpp> // To handle the inputs
#include <memory>
#include <utility>

/// Namespace of SpaceInvaders
namespace si {

/// Namespace of Model View Controller
namespace mvc {

/**
 * The controller of the MVC
 */
class Controller
{
public:
        Controller(float cycles_per_second, std::shared_ptr<Model> model);

        /**
         \n Main Function of the controller
         \n @param window The sfml window the player sees and interacts with
         */
        void handleInput(sf::RenderWindow& window) const; // Could be const as we deal with pointers anyway???

        /**
         \n Handles the input during the titleScreen
         \n @param window The sfml window the player sees and interacts with
         */
        void handleTitleScreenInput(sf::RenderWindow& window) const;

        /**
         \n Updates the movement of the aliens
         \n Updates the bullets
         \n Check if any objects collided and delete them if needed
         */
        void updateModel();

        /**
         *
         * @param window
         */
        void handleGameOverScreenInput(sf::RenderWindow& window) const;

private:
        /// The number of logic cycles per second the game should make
        float cyclesPerSecond;

        /// The model the controller controls
        std::shared_ptr<Model> model;

        /// Number of update cycles
        int updateCycles{0};

        /**
         \n
         \n @param origin
         \n @param bullet_type
         */
        void shoot(entity::Position origin, entity::Size size, unsigned int attack, int health, entity::bulletType bullet_type,
                   entity::MovePattern move_pattern, entity::colourType colour_type, bool fromPlayer) const;

        /**
         \n
         \n @param bullet
         */
        void addBulletToGame(entity::Bullet bullet) const;

        /**
         \n
         \n @param window
         */
        void handelEvent(sf::RenderWindow& window) const;

        void checkPlayer() const;
};

} // namespace mvc
} // namespace si

#endif // SPACEINVADERS_CONTROLLER_H
