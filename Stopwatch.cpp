//============================================================================
// Name        : Stopwatch.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Stopwatch.h"

std::shared_ptr<Stopwatch> Stopwatch::getInstance()
{
        if (!instance) { // The first time getInstance() is called
                instance = std::make_shared<Stopwatch>(Stopwatch{});
        }
        return instance;
}

void Stopwatch::restart() { start = clock(); }

float Stopwatch::getElapsedTime() const { return static_cast<float>(clock() - start) / CLOCKS_PER_SEC; }
