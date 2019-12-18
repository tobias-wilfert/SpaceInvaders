//============================================================================
// Name        : Level.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_LEVEL_H
#define SPACEINVADERS_LEVEL_H

#include "../Entity/Enemy.h"
#include "../Entity/Counter.h"
#include "../Entity/CollideObject.h"

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
public: // TODO: Before something can happen here I need a polymorphic class hierarchies for all the thing to add in
        Level();

private:
        /// Make Model friend of Model
        friend class Model;
        /// Make View friend of Model
        friend class View;
        /// Make Controller friend of Model
        friend class Controller;

        /// List of all entities that the view should draw
        std::deque<std::shared_ptr<entity::Entity>> listOfEntities;

        /// List of all the entities that need to be checked if they collide
        std::deque<std::shared_ptr<entity::CollideObject>> listOfCollideObjects;

        // Update all the alien movement -> could be specified in file as LLRR=(left,left,right,right)

        // List of all collide objects for the game logic
};
} // namespace mvc
} // namespace si

#endif // SPACEINVADERS_LEVEL_H
