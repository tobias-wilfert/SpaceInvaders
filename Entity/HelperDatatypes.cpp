//============================================================================
// Name        : HelperDatatypes.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "HelperDatatypes.h"

si::entity::Size::Size(float width, float height) : width(width), height(height) {}

si::entity::Position::Position(float x, float y) : x(x), y(y) {}

si::entity::Rectangle::Rectangle(const si::entity::Position& top_left, const si::entity::Position& bottom_right)
    : topLeft(top_left), bottomRight(bottom_right)
{
}

si::entity::MovePattern::MovePattern(std::string pattern, float step_size, float move_frequency)
    : pattern(std::move(pattern)), stepSize(step_size), moveFrequency(move_frequency)
{
}
