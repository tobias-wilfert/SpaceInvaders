//============================================================================
// Name        : Player.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_PLAYER_H
#define SPACEINVADERS_PLAYER_H

#include "Mortal.h"

/// Namespace of SpaceInvaders
namespace si {

/// Namespace of the Entity hierarchy
namespace entity {

/**
 * Character fo the player of th game (The space cannon)
 */
class Player : public Mortal
{
public:
        Player(const Size& size, const Position& position, unsigned int attack_points, collideObjectType type,
               int health_points);

        /**
         \n Override of getEntityType() from Entity
         \n @return The entity type of this entity
         */
        entityType getEntityType() const override;

private:
        /// The type of the entity
        entityType entity_type{entityType::player};
};

} // namespace entity
} // namespace si

#endif // SPACEINVADERS_PLAYER_H
