//============================================================================
// Name        : Counter.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_COUNTER_H
#define SPACEINVADERS_COUNTER_H

#include "Entity.h"

/**
 * Namespace of SpaceInvaders
 */
namespace si{

/**
 * Counter Class used for both Score and Life of the Player. This is possible
 * because the Model doesn't care about looks.
 * Derived from Entity as a counter has a position and size
 */
class Counter: private Entity
{
public:

        Counter(const Size& size, const Position& position, int value);

        /**
         * Returns the value the counter is keeping track of
         * @return The value the counter is keeping track of
         */
        int get_value() const;

        /**
         * Adjust the value the counter is keeping track of
         * @param value The new value the counter is keeping track of
         */
        void set_value(int value);

private:

        // Value the counter tracks
        int value{0};
};

}

#endif // SPACEINVADERS_COUNTER_H
