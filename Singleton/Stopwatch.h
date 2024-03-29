//============================================================================
// Name        : Stopwatch.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_STOPWATCH_H
#define SPACEINVADERS_STOPWATCH_H

#include <chrono>
#include <memory>

/// Namespace of SpaceInvaders
namespace si {

/// Namespace of Singleton Classes
namespace singleton {

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
        /**
         \n Checks if instance is a nullptr, if this is the case
         \n initialize instance with a new shared_ptr<Stopwatch> and return instance
         \n else return instance
         \n @return static std::shared_ptr<Stopwatch> instance
         */
        static std::shared_ptr<Stopwatch> getInstance();

        /**
         \n Sets start equal to clock()
         */
        void restart();

        /**
         \n Calculates the time(in Seconds) that elapsed since the last restart/construction,
         \n using the following formula: (current - start)
         \n @return Float representation of the number of Seconds that passed since the last restart/construction
         */
        float getElapsedTime() const;

private:
        /// Smart pointer to an instance of Stopwatch that is shared by all instances of Stopwatch
        static std::shared_ptr<Stopwatch> instance;

        /// The number of Clock ticks the program was at during the last restart/construction
        std::chrono::time_point<std::chrono::high_resolution_clock> start;

        /// Private constructor causing only 1 instance ot Stopwatch to be allowed
        Stopwatch();
};
} // namespace singleton
} // namespace si

#endif // SPACEINVADERS_STOPWATCH_H