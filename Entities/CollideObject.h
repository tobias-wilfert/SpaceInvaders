//============================================================================
// Name        : CollideObject.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_COLLIDEOBJECT_H
#define SPACEINVADERS_COLLIDEOBJECT_H

#include "Entity.h"

/**
 * Namespace of SpaceInvaders
 */
namespace si {

/**
 * CollideObjects are either Friend or Enemy
 * This allows that entity can ignore objects with the same time when checking for collision
 * As one Alien can't shoot another
 */
enum Type
{
        Friend,
        Enemy
};

/**
 * Class for all entities that can collide = everything (except Counters)
 */
class CollideObject: private Entity
{
public:
        CollideObject(const Size& size, const Position& position, Type type);

        /**
         \n Get the Rectangle surrounding the entity
         \n @return Rectangle that surrounds the object
         */
        Rectangle getBound() const;

private:

        // Type to clarify what you are safes time when checking
        Type type;
};

/**
 * Checks if the bounds of co1 and co2 overlap aka collide
 * @param co1 First collideObject to check
 * @param co2 Second collideObject to check
 * @return True if the objects collide else false
 */
bool collided(const CollideObject& co1, const CollideObject& co2);

}

#endif // SPACEINVADERS_COLLIDEOBJECT_H
