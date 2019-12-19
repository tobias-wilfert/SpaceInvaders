//============================================================================
// Name        : Enemy.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_ENEMY_H
#define SPACEINVADERS_ENEMY_H

#include "MoveObject.h"

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
class Enemy : public MoveObject
{
public:
        Enemy(const Size& size, const Position& position, unsigned int attack_points, collideObjectType type,
              int health_points, const MovePattern& move_pattern, enemyType enemy_type, colourType colour);

        /**
         \n Override of getEntityType() from Entity
         \n @return The entity type of this entity
         */
        entityType getEntityType() const override;

        /**
         \n Get the type of the enemy
         \n @return enemyType representing the type of the alien
         */
        enemyType get_enemy_type() const;

        /**
         \n Get the colour of the player
         \n @return colourType representing the color of the alien
         */
        colourType get_colour() const;

        /**
         \n Get the state the enemy is in
         \n @return bool representing state 1 or 0
         */
        bool is_state() const;

        /**
         \n Set the state the enemy is in
         \n @param inputState the stat th enemy should be set to
         */
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
