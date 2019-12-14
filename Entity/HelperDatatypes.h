//============================================================================
// Name        : HelperDatatypes.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_HELPERDATATYPES_H
#define SPACEINVADERS_HELPERDATATYPES_H

///Namespace of SpaceInvaders
namespace si {

/// Namespace of the Entity hierarchy
namespace entity {
/**
 * Types of leaves in the Class hierarchy
 */
enum entityType
{
        counter,
        immortal,
        player,
        shield,
        enemy,
        bullet
};

/**
 * Size represented by 2 floats (width,height)
 */
struct Size
{

        Size(float width, float height);

        float width;
        float height;
};

/**
 * Position represented by (x,y)
 */
struct Position
{

        Position(float x, float y);

        float x;
        float y;
};

/**
 * Rectangle described by 2 Positions TopLeft and BottomRight
 */
struct Rectangle
{

        Rectangle(const Position& top_left, const Position& bottom_right);

        // Position of Top left corner
        Position topLeft;
        // Position of Bottom right corner
        Position bottomRight;
};

}
}

#endif // SPACEINVADERS_HELPERDATATYPES_H
