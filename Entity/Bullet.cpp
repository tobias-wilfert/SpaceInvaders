//============================================================================
// Name        : Bullet.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Bullet.h"

si::entity::Bullet::Bullet(const si::entity::Size& size, const si::entity::Position& position,
                           unsigned int attack_points, si::entity::collideObjectType type, int health_points,
                           float velocity)
    : Mortal(size, position, attack_points, type, health_points), velocity(velocity)
{
}

si::entity::entityType si::entity::Bullet::getEntityType() const { return entity_type; }
