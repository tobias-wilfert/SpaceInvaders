//============================================================================
// Name        : Immortal.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Immortal.h"

si::Immortal::Immortal(const si::Size& size, const si::Position& position, unsigned int attack_points,
    si::collideObjectType type)
    : CollideObject(size, position, attack_points, type)
{
}

bool si::Immortal::isDead() const { return false; }

void si::Immortal::collide(unsigned int damage) {/* Do nothing as damage is irrelevant*/}

si::entityType si::Immortal::getEntityType() const { return entity_type; }


