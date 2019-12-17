//============================================================================
// Name        : Player.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Player.h"

si::entity::Player::Player(const si::entity::Size& size, const si::entity::Position& position,
                           unsigned int attack_points, si::entity::collideObjectType type, int health_points)
    : Mortal(size, position, attack_points, type, health_points)
{
}

si::entity::entityType si::entity::Player::getEntityType() const { return entity_type; }
