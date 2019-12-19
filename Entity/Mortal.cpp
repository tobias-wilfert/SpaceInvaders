//============================================================================
// Name        : Mortal.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Mortal.h"

si::entity::Mortal::Mortal(const si::entity::Size& size, const si::entity::Position& position,
                           unsigned int attack_points, si::entity::collideObjectType type, int health_points)
    : CollideObject(size, position, attack_points, type), healthPoints(health_points),
      initialHealthPoints(health_points)
{
}

int si::entity::Mortal::get_health_points() const { return healthPoints; }

bool si::entity::Mortal::isDead() const { return healthPoints <= 0; }

void si::entity::Mortal::collide(unsigned int damage) { healthPoints -= damage; }

int si::entity::Mortal::get_initial_health_points() const { return initialHealthPoints; }
