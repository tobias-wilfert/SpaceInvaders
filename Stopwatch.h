//============================================================================
// Name        : Stopwatch.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_STOPWATCH_H
#define SPACEINVADERS_STOPWATCH_H

#include <ctime>
#include <memory>

// TODO: Add description

/**
 \n Inspiration: https://www.tutorialspoint.com/Explain-Cplusplus-Singleton-design-pattern
 \n A Singleton implementation of a Stopwatch
 \n Usage:
 \n std::shared_ptr<Stopwatch> Stopwatch::instance = nullptr;
 \n As Non-const static member must be initialized out of line
 \n std::shared_ptr<Stopwatch> s = Stopwatch::getInstance();
 */
class Stopwatch
{
public:
        static std::shared_ptr<Stopwatch> getInstance();

        void restart();

        float getElapsedTime() const;

private:

        static std::shared_ptr<Stopwatch> instance;

        clock_t start;

        // Private constructor -> allows only 1 instance ot Stopwatch
        Stopwatch() : start{clock()} {};
};

#endif // SPACEINVADERS_STOPWATCH_H