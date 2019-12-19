//============================================================================
// Name        : Level.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_LEVEL_H
#define SPACEINVADERS_LEVEL_H

#include "../Entity/Bullet.h"
#include "../Entity/CollideObject.h"
#include "../Entity/Counter.h"
#include "../Entity/Enemy.h"
#include "../Entity/Shield.h"

#include <deque>
#include <memory>
#include <string>

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
public:
        Level();

        /**
         \n Returns true if the level is completed (no more enemies are left)
         \n @return True if all enemies are dead
         */
        bool is_level_complete() const;

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

        /// List of all the bullets
        std::deque<std::shared_ptr<entity::Bullet>> listOfBullets;
};
} // namespace mvc
} // namespace si

#endif // SPACEINVADERS_LEVEL_H
