//============================================================================
// Name        : Mortal.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Mortal.h"

si::Mortal::Mortal(const si::Size& size, const si::Position& position, unsigned int attack_points,
    si::collideObjectType type, int health_points)
    : CollideObject(size, position, attack_points, type), healthPoints(health_points)
{
}

int si::Mortal::get_health_points() const { return healthPoints; }

bool si::Mortal::isDead() const { return healthPoints <= 0; }

void si::Mortal::collide(unsigned int damage) {healthPoints -= damage;}

