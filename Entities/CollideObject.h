//
// Created by Tobias Wilfert on 12/12/2019.
//

#ifndef SPACEINVADERS_COLLIDEOBJECT_H
#define SPACEINVADERS_COLLIDEOBJECT_H

#include "Entity.h"

// Namespace to avoid name collision
namespace si {

enum Type
{
        Friend,
        Enemy
};

/**
 * Every thing that can collide (not score)
 */
class CollideObject: private Entity
{
public:

        Rectangle getBound() const;

private:
        // Type to clarify what you are
        Type type;
};

bool collided(const CollideObject& co1, const CollideObject& co2);

}

#endif // SPACEINVADERS_COLLIDEOBJECT_H
