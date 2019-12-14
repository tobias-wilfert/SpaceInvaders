//============================================================================
// Name        : Level.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_LEVEL_H
#define SPACEINVADERS_LEVEL_H

#include "Entity/Counter.h"

/**
 * Namespace of SpaceInvaders
 */
namespace si {

/**
 \n The product of the parser
 \n The model containing all entities
 \n The view will use this to draw
 \n The controller will change things from here
 \n Maybe smart to add to the Model -> so that View and Controller act on the model and not on the individual levels
 */
class Level
{
        // TODO: Before something can happen here I need a polymorphic class hierarchies for all the thing to add in here
public:
private:
        // Track the health of the player
        entity::Counter healthCounter;

        // Track the score
        entity::Counter scoreCounter;
        
};

}

#endif // SPACEINVADERS_LEVEL_H
