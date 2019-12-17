//============================================================================
// Name        : Shield.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_SHIELD_H
#define SPACEINVADERS_SHIELD_H

#include "Mortal.h"

/// Namespace of SpaceInvaders
namespace si{

/// Namespace of the Entity hierarchy
namespace entity {

/**
 * The shields the player can hide behind
 */
class Shield : public Mortal
{
public:
        Shield(const Size& size, const Position& position, unsigned int attack_points, collideObjectType type,
               int health_points);

        /**
         * Override of getEntityType() from Entity
         * @return The entity type of this entity
         */
        entityType getEntityType() const override;

private:
        /// The type of the entity
        entityType entity_type{entityType::shield};
};

}
}

#endif // SPACEINVADERS_SHIELD_H
