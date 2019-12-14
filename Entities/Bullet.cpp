//============================================================================
// Name        : Bullet.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Bullet.h"

si::Bullet::Bullet(const si::Size& size, const si::Position& position, unsigned int attack_points,
                   si::collideObjectType type, int health_points, float velocity)
    : Mortal(size, position, attack_points, type, health_points), velocity(velocity)
{
}

si::entityType si::Bullet::getEntityType() const { return entity_type; }
