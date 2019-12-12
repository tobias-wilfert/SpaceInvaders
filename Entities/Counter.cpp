//
// Created by Tobias Wilfert on 12/12/2019.
//

#include "Counter.h"

si::Counter::Counter(const si::Size& size, const si::Position& position, int value)
    : Entity(size, position), value(value)
{
}

int si::Counter::get_value() const { return value; }

void si::Counter::set_value(int value) { Counter::value = value; }


