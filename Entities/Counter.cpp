//
// Created by Tobias Wilfert on 12/12/2019.
//

#include "Counter.h"

si::Counter::Counter(const si::Size& size, const si::Position& position, int value, si::counterType counter_type)
    : Entity(size, position), value(value), counter_type(counter_type)
{
}

int si::Counter::get_value() const { return value; }

void si::Counter::set_value(int inputValue) { Counter::value = inputValue; }

si::entityType si::Counter::getEntityType() const { return entity_type; }

si::counterType si::Counter::get_counter_type() const { return counter_type; }

