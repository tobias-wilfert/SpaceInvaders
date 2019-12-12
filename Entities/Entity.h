//============================================================================
// Name        : Entity.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_ENTITY_H
#define SPACEINVADERS_ENTITY_H

#include "HelperDatatypes.h"

/**
 * Namespace of SpaceInvaders
 */
namespace si{

/**
 * Base class of all items in the game
 * As all have a Position and Size
 */
class Entity
{
public:

        Entity(const Size& size, const Position& position);

        // The size of the entity
        Size size;

        // The position of the entity
        Position position;

private:

};

}

#endif // SPACEINVADERS_ENTITY_H
