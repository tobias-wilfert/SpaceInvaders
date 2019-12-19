//============================================================================
// Name        : Counter.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_COUNTER_H
#define SPACEINVADERS_COUNTER_H

#include "Entity.h"

/// Namespace of SpaceInvaders
namespace si {

/// Namespace of the Entity hierarchy
namespace entity {
/**
 * Type of the counter either health or score needed because view displays them differently
 */
enum counterType
{
        health,
        score,
        cooldown
};

/**
 \n Counter Class used for both Score, Life and Cooldown of the Player.
 \n This is possible because the Model doesn't care about looks.
 \n Derived from Entity as a counter has a position and size
 */
class Counter : public Entity
{
public:
        Counter(const Size& size, const Position& position, int value, counterType counter_type);

        /**
         \n Returns the value the counter is keeping track of
         \n @return The value the counter is keeping track of
         */
        int get_value() const;

        /**
         \n Adjust the value the counter is keeping track of
         \n @param inputValue The new value the counter is keeping track of
         */
        void set_value(int inputValue);

        /**
         \n Returns the type of the counter to distinguish between healthCounter and scoreCounter
         \n @return value of enum CounterType to indicate the type of this counter
         */
        counterType get_counter_type() const;

        /**
         \n Override of getEntityType() from Entity
         \n @return The entity type of this entity
         */
        entityType getEntityType() const override;

private:
        /// Value the counter tracks
        int value;

        /// The type of counter, determines how view draws this
        counterType counter_type;

        /// The type of the entity
        entityType entity_type{entityType::counter};
};

} // namespace entity
} // namespace si

#endif // SPACEINVADERS_COUNTER_H
