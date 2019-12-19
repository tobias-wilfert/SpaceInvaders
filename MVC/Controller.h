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
#include <random>
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
         \n Handles the input during the end screen (Win / GameOver)
         \n @param window The sfml window the player sees and interacts with
         */
        void handleGameEndScreenInput(sf::RenderWindow& window) const;

private:
        /// The number of logic cycles per second the game should make
        float cyclesPerSecond;

        /// The model the controller controls
        std::shared_ptr<Model> model;

        /// Number of update cycles
        int updateCycles{0};

        /**
         * An bullet is created for the player to shoot and addBulletToGame is called
         */
        void playerShoot() const;

        /**
         \n An bullet is created for the enemy to shoot and addBulletToGame is called
         \n @param enemy The enemy that shoots the bullet
         */
        void alienShoot(const std::shared_ptr<si::entity::Enemy>& enemy) const;

        /**
         \n Adds bullet to the model
         \n @param bullet The bullet to add to the model
         */
        void addBulletToGame(entity::Bullet bullet) const;

        /**
         \n Handles smlf Events like closing window
         \n @param window The sfml window the users sees and interacts with
         */
        void handelEvent(sf::RenderWindow& window) const;

        /**
         \n Checks if the player is currently destroyed, if yes re-spawn the player
         \n ( Decrement the health Counter, set player health to its initial health and set to re-spawning)
         */
        void checkPlayer() const;

        /**
         \n Move all the objects in levels listOfCollideObjects
         \n Check if an alien touches he ground, if yes GameOver
         \n Let a random alien shoot a bullet
         */
        void moveObjects();

        /**
         * Checks if any objects in levels listOfCollideObjects collided with another
         */
        void checkCollisions() const;

        /**
         * Check if any bullet is destroyed if yes delete it
         */
        void cleanUpBullets() const;

        /**
         * Check if any collideObject is destroyed if yes delete it
         */
        void cleanUpCollideObjects() const;

        /**
         \n Update the Score of the level after an enemy is destroyed
         \n @param enemy The enemy that just got destroyed
         */
        void updateScore(const std::shared_ptr<entity::Enemy>& enemy) const;

        /**
         * Check if any entity is destroyed if yes delete it
         */
        void cleanUpEntities() const;

        /// The frequency the player is allowed to shoot at
        int shootFrequency{100};
};

} // namespace mvc
} // namespace si

#endif // SPACEINVADERS_CONTROLLER_H
