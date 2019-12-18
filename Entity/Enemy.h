//============================================================================
// Name        : Enemy.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_ENEMY_H
#define SPACEINVADERS_ENEMY_H

#include "Mortal.h"

/// Namespace of SpaceInvaders
namespace si {

/// Namespace of the Entity hierarchy
namespace entity {

/**
 * Types of different aliens
 */
enum enemyType
{
        a,
        b,
        c,
        m,
};

/**
 * Class for all Enemies may serve as a base class for even more of them
 */
class Enemy : public Mortal
{
public:
        Enemy(const Size& size, const Position& position, unsigned int attack_points, collideObjectType type,
              int health_points, enemyType enemy_type, colourType colour);

        /**
         * Override of getEntityType() from Entity
         * @return The entity type of this entity
         */
        entityType getEntityType() const override;

        // TODO:: Document

        enemyType get_enemy_type() const;

        colourType get_colour() const;

        bool is_state() const;

        void set_state(bool inputState);

private:
        /// The type of the entity
        entityType entity_type{entityType::enemy};

        /// State as some enemies have different appearances
        bool state{false};

        /// The type of the enemy
        enemyType enemy_type;

        /// Color of the enemy
        colourType colour;
};

} // namespace entity
} // namespace si

#endif // SPACEINVADERS_ENEMY_H
