//============================================================================
// Name        : Stopwatch.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Stopwatch.h"

Stopwatch* Stopwatch::getInstance()
{
        if (!instance) {
                instance = new Stopwatch{};
        }
        return instance;
}

void Stopwatch::restart() { start = clock(); }

float Stopwatch::getElapsedTime() const { return static_cast<float>(clock() - start) / CLOCKS_PER_SEC; }
