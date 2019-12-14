//============================================================================
// Name        : Counter.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Counter.h"

si::entity::Counter::Counter(const si::entity::Size& size, const si::entity::Position& position, int value, si::entity::counterType counter_type)
    : Entity(size, position), value(value), counter_type(counter_type)
{
}

int si::entity::Counter::get_value() const { return value; }

void si::entity::Counter::set_value(int inputValue) { Counter::value = inputValue; }

si::entity::entityType si::entity::Counter::getEntityType() const { return entity_type; }

si::entity::counterType si::entity::Counter::get_counter_type() const { return counter_type; }

