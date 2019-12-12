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

void Stopwatch::restart() { start = std::chrono::high_resolution_clock::now(); }

float Stopwatch::getElapsedTime() const
{
        std::chrono::duration<float> diff = std::chrono::high_resolution_clock::now() - start;
        return diff.count();
}

Stopwatch::Stopwatch() : start(std::chrono::high_resolution_clock::now()) {}

