//============================================================================
// Name        : Mortal.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_MORTAL_H
#define SPACEINVADERS_MORTAL_H

#include "CollideObject.h"

/// Namespace of SpaceInvaders
namespace si {

/// Namespace of the Entity hierarchy
namespace entity {

/**
 \n All collide objects that have hp(can die / take damage on collision)
 \n -> Player, Enemies, Shields
 */
class Mortal : public CollideObject
{
public:
        Mortal(const Size& size, const Position& position, unsigned int attack_points, collideObjectType type,
               int health_points);

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
        void collide(unsigned int input_damage) override;

        /**
         \n Returns an int representation of the healthPoints
         \n @return healthPoints
         */
        int get_health_points() const;

        /**
         \n Returns the initial health of the entity (Important for % health remaining)
         \n @return initialHealthPoints
         */
        int get_initial_health_points() const;

        /**
         \n Set health points to initialHealth Points
         */
        void resetHealthPoints();

private:
        /// The HP of the Entity
        int healthPoints;

        /// The HP the entity started of with
        int initialHealthPoints;
};

} // namespace entity
} // namespace si

#endif // SPACEINVADERS_MORTAL_H
