//============================================================================
// Name        : MoveObject.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_MOVEOBJECT_H
#define SPACEINVADERS_MOVEOBJECT_H

#include "Mortal.h"

/// Namespace of SpaceInvaders
namespace si {

/// Namespace of the Entity hierarchy
namespace entity {

/**
 * Class for everything that moves during the game in a pre determined pattern
 */
class MoveObject: public Mortal
{
public:
        MoveObject(const Size& size, const Position& position, unsigned int attack_points, collideObjectType type,
                   int health_points, MovePattern  move_pattern);

        /**
         *
         */
        void move();

        /**
         *
         */
        void takeStep();

private:
        /// The pattern the object will move with
        MovePattern move_pattern;

};

}
}

#endif // SPACEINVADERS_MOVEOBJECT_H