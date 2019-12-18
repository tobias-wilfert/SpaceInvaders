//============================================================================
// Name        : Bullet.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Bullet.h"

si::entity::Bullet::Bullet(const si::entity::Size& size, const si::entity::Position& position,
    unsigned int attack_points, si::entity::collideObjectType type, int health_points,
    const si::entity::MovePattern& move_pattern, si::entity::bulletType bullet_type)
    : MoveObject(size, position, attack_points, type, health_points, move_pattern), bullet_type(bullet_type)
{
}

si::entity::entityType si::entity::Bullet::getEntityType() const { return entity_type; }
