//============================================================================
// Name        : Stopwatch.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Stopwatch.h"



std::shared_ptr<Stopwatch> Stopwatch::getInstance()
{
        auto deleter = [](Stopwatch*p){
          std::cout << "[deleter called]\n"; delete p;
        };

        if (!instance) {
                //instance = std::make_shared<Stopwatch>(Stopwatch{});
                instance = std::shared_ptr<Stopwatch>(new Stopwatch,deleter);
        }
        return instance;
}

void Stopwatch::restart() { start = clock(); }

float Stopwatch::getElapsedTime() const { return static_cast<float>(clock() - start) / CLOCKS_PER_SEC; }

Stopwatch::~Stopwatch(){
        std::cout << "~Stopwatch" << std::endl;
}
