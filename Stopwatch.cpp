//============================================================================
// Name        : Stopwatch.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Stopwatch.h"

std::shared_ptr<Stopwatch> Stopwatch::getInstance()
{
        if (!instance) {
                instance = std::make_shared<Stopwatch>(Stopwatch{});
        }
        return instance;
}

void Stopwatch::restart() { start = clock(); }


// TODO: Ask the prof about this not working correctly
float Stopwatch::getElapsedTime() const { return static_cast<float>(clock() - start) / CLOCKS_PER_SEC; }
