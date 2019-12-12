//============================================================================
// Name        : Entity.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_ENTITY_H
#define SPACEINVADERS_ENTITY_H


// Namespace to avoid name collision
namespace si{

// As all inherit from Entity why  not declare it here?
struct Size{

        Size(float width, float height);

        float width;
        float height;
};

struct Position{

        Position(float x, float y);

        float x;
        float y;
};


struct Rectangle{

        Rectangle(const Position& top_left, const Position& bottom_right);

        // Top left corner
        Position topLeft;
        // Bottom right corner
        Position bottomRight;
};

/**
 * Abstract base class for all entities
 * -> Should entity have all virtual function members?
 */
class Entity
{
public:

        Size size;

        Position position;

private:

};

}

#endif // SPACEINVADERS_ENTITY_H
