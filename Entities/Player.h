//============================================================================
// Name        : Player.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_PLAYER_H
#define SPACEINVADERS_PLAYER_H

#include "Mortal.h"

/**
 * Namespace of SpaceInvaders
 */
namespace si{

/**
 * Character fo the player of th game (The space cannon)
 */
class Player: private Mortal
{
public:
        Player(const Size& size, const Position& position, unsigned int attack_points, collideObjectType type,
               int health_points);

        /**
         * Override of getEntityType() from Entity
         * @return The entity type of this entity
         */
        entityType getEntityType() const override;

private:

        // The type of the entity
        entityType entity_type{entityType::player};

};

}

#endif // SPACEINVADERS_PLAYER_H
