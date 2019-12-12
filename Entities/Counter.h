//
// Created by Tobias Wilfert on 12/12/2019.
//

#ifndef SPACEINVADERS_COUNTER_H
#define SPACEINVADERS_COUNTER_H

#include "Entity.h"

namespace si{

/**
 * Counter for both life and Score
 */
class Counter: private Entity
{
public:

        // Getters and setters to acces should not be able to acces directly?
        // Just cleaner qua code

private:


        // Intitize to 0 and then to 3/4 or life
        int value;

};

}

#endif // SPACEINVADERS_COUNTER_H
