//============================================================================
// Name        : Shield.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Shield.h"

si::Shield::Shield(const si::Size& size, const si::Position& position, unsigned int attack_points,
                   si::collideObjectType type, int health_points)
    : Mortal(size, position, attack_points, type, health_points)
{
}

si::entityType si::Shield::getEntityType() const { return entity_type; }
