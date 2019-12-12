//============================================================================
// Name        : Entity.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Entity.h"

// Helper Structs

si::Size::Size(float width, float height) : width(width), height(height) {}

si::Position::Position(float x, float y) : x(x), y(y) {}

si::Rectangle::Rectangle(const si::Position& top_left, const si::Position& bottom_right)
    : topLeft(top_left), bottomRight(bottom_right)
{
}
