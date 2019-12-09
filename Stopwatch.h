//============================================================================
// Name        : Stopwatch.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_STOPWATCH_H
#define SPACEINVADERS_STOPWATCH_H

#include <ctime>

// TODO: Add Destructor
// TODO: Add description
// TODO: Make pointer shared pointer

/**
 \n Inspiration: https://www.tutorialspoint.com/Explain-Cplusplus-Singleton-design-pattern
 \n A Singleton implementation of a Stopwatch
 \n Usage:
 \n Stopwatch* Stopwatch::instance = nullptr;
 \n As Non-const static member must be initialized out of line
 \n Stopwatch* s = Stopwatch::getInstance();
 \n Cleaner than: Stopwatch *s = s->getInstance();
 */
class Stopwatch{
public:

    static Stopwatch* getInstance();

    void restart();

    float getElapsedTime() const;

private:

    static Stopwatch* instance;

    clock_t start;

    // Private constructor -> allows only 1 instance ot Stopwatch
    Stopwatch():start{clock()}{};

};

#endif //SPACEINVADERS_STOPWATCH_H