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
class MoveObject : public Mortal
{
public:
        MoveObject(const Size& size, const Position& position, unsigned int attack_points, collideObjectType type,
                   int health_points, MovePattern move_pattern);

        /**
         \n Tell the MoveObject it is time to move, because a MoveObject does not necessarily
         \n need to move every time the MoveObject may decide to not take a step
         */
        void move();

        /**
         \n Take a step as specified in move_pattern and jump to the next instruction in move_pattern
         */
        void takeStep();

private:
        /// The pattern the object will move with
        MovePattern move_pattern;
};

} // namespace entity
} // namespace si

#endif // SPACEINVADERS_MOVEOBJECT_H
