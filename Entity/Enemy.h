//============================================================================
// Name        : Enemy.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_ENEMY_H
#define SPACEINVADERS_ENEMY_H

#include "Mortal.h"

///Namespace of SpaceInvaders
namespace si {

/// Namespace of the Entity hierarchy
namespace entity {

/**
 * Class for all Enemies may serve as a base class for even more of them
 */
class Enemy : private Mortal
{
public:
        // TODO Add more features to the aliens
        Enemy(const Size& size, const Position& position, unsigned int attack_points, collideObjectType type,
              int health_points);

        /**
         * Override of getEntityType() from Entity
         * @return The entity type of this entity
         */
        entityType getEntityType() const override;

private:
        // The type of the entity
        entityType entity_type{entityType::enemy};
};

}
}

#endif // SPACEINVADERS_ENEMY_H
