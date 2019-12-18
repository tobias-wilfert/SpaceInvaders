//============================================================================
// Name        : Enemy.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Enemy.h"

si::entity::Enemy::Enemy(const si::entity::Size& size, const si::entity::Position& position, unsigned int attack_points,
    si::entity::collideObjectType type, int health_points,
    const si::entity::MovePattern& move_pattern, si::entity::enemyType enemy_type,
    si::entity::colourType colour)
    : MoveObject(size, position, attack_points, type, health_points, move_pattern), enemy_type(enemy_type),
      colour(colour)
{
}

si::entity::entityType si::entity::Enemy::getEntityType() const { return entity_type; }

si::entity::enemyType si::entity::Enemy::get_enemy_type() const { return enemy_type; }

si::entity::colourType si::entity::Enemy::get_colour() const { return colour; }

bool si::entity::Enemy::is_state() const { return state; }

void si::entity::Enemy::set_state(bool inputState) { Enemy::state = inputState; }

