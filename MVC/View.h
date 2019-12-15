//============================================================================
// Name        : View.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_VIEW_H
#define SPACEINVADERS_VIEW_H

#include "Model.h"

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

        // Main function to draw the Model
        void display(sf::RenderWindow& window ) const;

private:

        // Needs the model to display
        Model* model;

};

}
}

#endif // SPACEINVADERS_VIEW_H
