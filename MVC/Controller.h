//============================================================================
// Name        : Controller.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_CONTROLLER_H
#define SPACEINVADERS_CONTROLLER_H

#include "Model.h"

#include <memory>
// To handle the inputs
#include <SFML/Graphics.hpp>

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
        Controller(const std::shared_ptr<Model>& model);

        // Main function
        void handleInput(sf::RenderWindow& window ) const; // Could be const as we deal with pointers anyway???

        // Function to update the movement  of the alliens

        // Function to update the bullets

private:

        // Controller controls the Model
        std::shared_ptr<Model> model;

};

}
}

#endif // SPACEINVADERS_CONTROLLER_H
