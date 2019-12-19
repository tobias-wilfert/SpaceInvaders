//============================================================================
// Name        : HelperDatatypes.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_HELPERDATATYPES_H
#define SPACEINVADERS_HELPERDATATYPES_H

#include <string>
#include <utility>

/// Namespace of SpaceInvaders
namespace si {

/// Namespace of the Entity hierarchy
namespace entity {

/**
 * Types of leaves in the Class hierarchy (All types that are not abstract)
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
 * Possible Colours
 */
enum colourType
{
        white,
        red,
        green,
        blue,
        yellow,
        magenta,
        cyan
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

        /// Position of Top left corner
        Position topLeft;
        /// Position of Bottom right corner
        Position bottomRight;
};
/**
 * MovePattern of an entity describes how it will move in game
 */
struct MovePattern
{

        MovePattern(std::string  pattern, float step_size, float move_frequency);

        /// The pattern with char: U,D,L,R,N representing up, down, left, right and None respectively
        std::string pattern;
        /// The size of 1 step in the move pattern
        float stepSize;
        /// The frequency that steps are taken (update every moveFrequency cycles)
        float moveFrequency;
        /// Index of current char in the pattern
        unsigned int patternIndex{0};
        /// Cycles since last step was taken
        unsigned int cyclesSinceLastStep{1};

};

} // namespace entity
} // namespace si

#endif // SPACEINVADERS_HELPERDATATYPES_H
