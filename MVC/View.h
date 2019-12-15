//============================================================================
// Name        : View.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_VIEW_H
#define SPACEINVADERS_VIEW_H

#include "Model.h"

#include "../Singleton/Transformation.h"

#include <memory>
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
        View(const std::shared_ptr<Model>& model, const std::shared_ptr<singleton::Transformation>& transformation);

        // Main function to draw the Model
        void display(sf::RenderWindow& window ) const;

private:

        // Needs the model to display
        std::shared_ptr<Model> model;

        // Used to transform from the [-4,4]x[-3, 3] logic of the Model
        // to the [0,windowHeight]x[0,windowWidth] logic of the view
        std::shared_ptr<singleton::Transformation> transformation;
};

}
}

#endif // SPACEINVADERS_VIEW_H
