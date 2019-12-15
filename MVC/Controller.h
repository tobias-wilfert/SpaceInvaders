//============================================================================
// Name        : Controller.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_CONTROLLER_H
#define SPACEINVADERS_CONTROLLER_H

#include "Model.h"

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
        // Main function
        void handleInput(sf::RenderWindow& window ) const; // Could be const as we deal with pointers anyway???

        // Function to update the movement  of the alliens

        // Function to update the bullets

private:

        // Controller controls the Model
        Model* model;

};

}
}

#endif // SPACEINVADERS_CONTROLLER_H
