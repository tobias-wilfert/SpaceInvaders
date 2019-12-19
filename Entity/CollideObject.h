//============================================================================
// Name        : CollideObject.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_COLLIDEOBJECT_H
#define SPACEINVADERS_COLLIDEOBJECT_H

#include "Entity.h"
#include <memory>
#include <stdexcept>

/// Namespace of SpaceInvaders
namespace si {

/// Namespace of the Entity hierarchy
namespace entity {

/**
 \n CollideObjects are either friendly, hostile or passive
 \n This allows that entity can ignore objects with the same type saving time when checking for collision
 */
enum collideObjectType
{
        friendly,
        hostile,
        passive
};

/**
 * Class for all entities that can collide = everything (except Counters)
 */
class CollideObject : public Entity
{
public:
        CollideObject(const Size& size, const Position& position, unsigned int attack_points, collideObjectType type);

        /**
         \n Get the Rectangle surrounding the entity
         \n @return Rectangle that surrounds the object
         */
        Rectangle getBound() const;

        /**
         \n Returns the type of collide object
         \n @return The collide object type of the object
         */
        collideObjectType get_type() const;

        /**
         \n Checks if an object is already destroyed
         \n Necessary as first all collision are detected and then all the items can be deleted
         \n @return True if it is already destroyed False if not
         */
        bool is_destroyed() const;

        /**
         \n Sets the value of destroyed indicating that an object should be deleted from the model asap
         \n @param destroyed True if it destroyed else false
         */
        void set_destroyed(bool destroyed);

        /**
         \n Returns the attack points
         \n @return An int representation of the attackPoints
         */
        unsigned int get_attack_points() const;

        /**
         \n Subtracts damage from the hp
         \n @param damage The damaged caused
         */
        virtual void collide(unsigned int damage) = 0;

        /**
         \n Checks if HP is below 0 a.k.a the entity is dead
         */
        virtual bool isDead() const = 0;

private:
        /// The damage an object causes when collided with
        unsigned int attackPoints;

        /// True it the collide Object is already destroyed
        bool destroyed{false};

        /// Type to clarify what you are safes time when checking
        collideObjectType type;
};

/**
 * Checks if the bounds of co1 and co2 overlap aka collide
 * @param co1 First collideObject to check
 * @param co2 Second collideObject to check
 * @return True if the objects collide else false
 */
bool collided(const CollideObject& co1, const CollideObject& co2);

/**
 \n Checks that:
 \n 1.) co1 and co2 are both not destroyed
 \n 2.) co1 and co2 are not dead -> throws an logic_error
 \n 3.) co1 and co2 collided
 \n If yes, the 2 objects collided decreasing each others HealthPoint with there AttackPoints
 \n If one of the objects is now dead set it to destroyed
 \n @param co1 pointer to the first collideObject
 \n @param co2 pointer to the second collideObject
 */
void checkCollision(const std::shared_ptr<CollideObject>& co1, const std::shared_ptr<CollideObject>& co2);

} // namespace entity
} // namespace si

#endif // SPACEINVADERS_COLLIDEOBJECT_H
