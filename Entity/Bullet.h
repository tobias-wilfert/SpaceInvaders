//============================================================================
// Name        : Bullet.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_BULLET_H
#define SPACEINVADERS_BULLET_H

#include "MoveObject.h"

/// Namespace of SpaceInvaders
namespace si {

/// Namespace of the Entity hierarchy
namespace entity {

/**
 * Types of different bullets
 */
enum bulletType
{
        up,
        down,
        laser
};

/**
 * All the bullets, the once from the player and from the enemies
 */
class Bullet : public MoveObject
{
public:
        Bullet(const Size& size, const Position& position, unsigned int attack_points, collideObjectType type,
               int health_points, const MovePattern& move_pattern, bulletType bullet_type, colourType colour_type);

        /**
         \n Override of getEntityType() from Entity
         \n @return The entity type of this entity
         */
        entityType getEntityType() const override;

        /**
         \n Returns the type of the bullet
         \n @return bulletType representing the type of the bullet
         */
        bulletType get_bullet_type() const;

        /**
         \n Returns the colour of the bullet
         \n @return colour_type
         */
        colourType get_colour_type() const;

private:
        /// The type of the entity
        entityType entity_type{entityType::bullet};

        /// The type of the bullet
        bulletType bullet_type;

        /// The color of the bullet
        colourType colour_type;
};

} // namespace entity
} // namespace si

#endif // SPACEINVADERS_BULLET_H
