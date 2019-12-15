//============================================================================
// Name        : Model.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_MODEL_H
#define SPACEINVADERS_MODEL_H

/// Namespace of SpaceInvaders
namespace si {

/// Namespace of Model View Controller
namespace mvc {

/**
 * The Model of the MVC
 */
class Model
{
public:

        // View needs a list of entities it can draw and cast if extra info is needed

        // Controller just needs to update player position

        // - Update all the bullets movement

        // - Update all the alien movement -> could be specified in file as LLRR=(left,left,right,right)


private:
        // All of the info the Model holds

        // Model should hold some items

        // While others should be held by the level
        // -> Player, Counter and immortal are independent of level
        //   L-> Maybe change position but that is all
        // -> Aliens, Bullets and Shields are level dependent

        // List of all entities for view to draw

        // Player, Counter and Immortal

        // List of all collide objects for the game logic

};

}
}

#endif // SPACEINVADERS_MODEL_H
