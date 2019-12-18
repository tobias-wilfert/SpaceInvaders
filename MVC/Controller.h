//============================================================================
// Name        : Controller.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_CONTROLLER_H
#define SPACEINVADERS_CONTROLLER_H

#include "Model.h"
#include "../Singleton/Stopwatch.h"
#include "Level.h"


#include <memory>
#include <utility>
#include <SFML/Graphics.hpp> // To handle the inputs

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
        Controller(float cycles_per_second, std::shared_ptr<Model>  model,
                   std::shared_ptr<singleton::Stopwatch>  stopwatch);

        /**
         * Main Function of the controller
         * @param window The sfml window the player sees and interacts with
         */
        void handleInput(sf::RenderWindow& window) const; // Could be const as we deal with pointers anyway???

        /**
         * Handles the input during the titleScreen
         * @param window The sfml window the player sees and interacts with
         */
        void handleTitleScreenInput(sf::RenderWindow& window) const;

        /**
         \n Updates the movement of the aliens
         \n Updates the bullets
         */
        void updateModel() const;

private:

        /// The number of logic cycles per second the game should make
        float cyclesPerSecond;

        /// The model the controller controls
        std::shared_ptr<Model> model;

        /// Stopwatch used to clock the Model and Controller -> making Speed PC independent
        std::shared_ptr<singleton::Stopwatch> stopwatch;
};


} // namespace mvc
} // namespace si

#endif // SPACEINVADERS_CONTROLLER_H
