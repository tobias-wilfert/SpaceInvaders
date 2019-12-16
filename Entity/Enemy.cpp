//============================================================================
// Name        : Enemy.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Enemy.h"

si::entity::Enemy::Enemy(const si::entity::Size& size, const si::entity::Position& position, unsigned int attack_points,
                 si::entity::collideObjectType type, int health_points)
    : Mortal(size, position, attack_points, type, health_points)
{
}

si::entity::entityType si::entity::Enemy::getEntityType() const { return entity_type; }