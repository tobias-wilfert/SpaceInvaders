//============================================================================
// Name        : Shield.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Shield.h"

si::entity::Shield::Shield(const si::entity::Size& size, const si::entity::Position& position,
                           unsigned int attack_points, si::entity::collideObjectType type, int health_points)
    : Mortal(size, position, attack_points, type, health_points), initialHealth(health_points)
{
}

si::entity::entityType si::entity::Shield::getEntityType() const { return entity_type; }

int si::entity::Shield::get_initial_health() const { return initialHealth; }
