//============================================================================
// Name        : Level.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_LEVEL_H
#define SPACEINVADERS_LEVEL_H

#include "../Entity/Counter.h"

#include <deque>
#include <memory>

/// Namespace of SpaceInvaders
namespace si {

/// Namespace of Model View Controller
namespace mvc {

/**
 \n The product of the parser
 \n The model containing all entities
 \n The view will use this to draw
 */
class Level
{
        // TODO: Before something can happen here I need a polymorphic class hierarchies for all the thing to add in
        // here
public:
private:
        /// Make Model friend of Model
        friend class Model;
        /// Make View friend of Model
        friend class View;
        /// Make Controller friend of Model
        friend class Controller;

        std::deque<std::shared_ptr<entity::Entity>> listOfEntities;
};
} // namespace mvc
} // namespace si

#endif // SPACEINVADERS_LEVEL_H
