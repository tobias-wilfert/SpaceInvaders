//============================================================================
// Name        : Bullet.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_BULLET_H
#define SPACEINVADERS_BULLET_H

#include "Mortal.h"


///Namespace of SpaceInvaders
namespace si {

/// Namespace of the Entity hierarchy
namespace entity {

/**
 * All the bullets, the once from the player and from the enemies
 */
class Bullet : private Mortal
{
public:
        // TODO: Add features
        Bullet(const Size& ize, const Position& position, unsigned int attack_points, collideObjectType type,
               int health_points, float velocity);

private:
        /**
         * Override of getEntityType() from Entity
         * @return The entity type of this entity
         */
        entityType getEntityType() const override;

public:
        // Velocity of the bullet
        float velocity;

        // The type of the entity
        entityType entity_type{entityType::bullet};
};

}
}

#endif // SPACEINVADERS_BULLET_H
