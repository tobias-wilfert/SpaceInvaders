//============================================================================
// Name        : Immortal.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_IMMORTAL_H
#define SPACEINVADERS_IMMORTAL_H

#include "CollideObject.h"


///Namespace of SpaceInvaders
namespace si {

/// Namespace of the Entity hierarchy
namespace entity {

/**
 * Class for the sky and the ground that should not die when hit by a bullet
 */
class Immortal : public CollideObject
{
public:
        Immortal(const Size& size, const Position& position, unsigned int attack_points, collideObjectType type);

        /**
         \n Override of isDead() from CollideObject
         \n Checks if HP is below 0 a.k.a the entity is dead returns always false
         */
        bool isDead() const override;

        /**
         \n Override of collide() from CollideObject
         \n Subtracts damage from the hp
         \n @param damage The damaged caused
         */
        void collide(unsigned int damage) override;

        /**
         * Override of getEntityType() from Entity
         * @return The entity type of this entity
         */
        entityType getEntityType() const override;

private:
        /// The type of the entity
        entityType entity_type{entityType::immortal};
};

}
}

#endif // SPACEINVADERS_IMMORTAL_H
