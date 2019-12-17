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
 * Counter Class used for both Score and Life of the Player. This is possible
 * because the Model doesn't care about looks.
 * Derived from Entity as a counter has a position and size
 */
class Counter : public Entity
{
public:
        Counter(const Size& size, const Position& position, int value, counterType counter_type);

        /**
         * Returns the value the counter is keeping track of
         * @return The value the counter is keeping track of
         */
        int get_value() const;

        /**
         * Adjust the value the counter is keeping track of
         * @param inputValue The new value the counter is keeping track of
         */
        void set_value(int inputValue);

        /**
         * Returns the type of the counter to distinguish between healthCounter and scoreCounter
         * @return value of enum CounterType to indicate the type of this counter
         */
        counterType get_counter_type() const;

        /**
         * Override of getEntityType() from Entity
         * @return The entity type of this entity
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

}
}

#endif // SPACEINVADERS_COUNTER_H
