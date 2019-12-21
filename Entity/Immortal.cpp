//============================================================================
// Name        : Immortal.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Immortal.h"

si::entity::Immortal::Immortal(const si::entity::Size& size, const si::entity::Position& position,
                               unsigned int attack_points, si::entity::collideObjectType type)
    : CollideObject(size, position, attack_points, type)
{
}

bool si::entity::Immortal::isDead() const { return false; }

void si::entity::Immortal::collide(unsigned int damage)
{ /* Do nothing as damage is irrelevant. Yet needed as function is override of another*/
}

si::entity::entityType si::entity::Immortal::getEntityType() const { return entity_type; }
