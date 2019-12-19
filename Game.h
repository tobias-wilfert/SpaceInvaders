//============================================================================
// Name        : Game.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

// Sadly needed here to handle the window
// Model should never know about this, view and control very much need this
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "MVC/Controller.h"
#include "MVC/Level.h"
#include "MVC/Model.h"
#include "MVC/View.h"
#include "Singleton/Stopwatch.h"
#include "Singleton/Transformation.h"


// TODO Match Types to reduce warnings in code inspect

/// Namespace of SpaceInvaders
namespace si {

/**
 \n An object that combines the different parts of the game.
 */
class Game
{
public:
        explicit Game(float cycles_per_second);

        /**
         \n The main function of game
         */
        void execute();

        /**
         \n Gets the resolution of the screen and uses these values to initialize transformation.
         \n Initializes stopwatch
         */
        void initialize();

private:
        /// The score of the player
        int score{0};

        /// The number of level the Player is currently at
        int levelNr{1};

        /// The number of logic cycles per second the game should make
        float cyclesPerSecond;

        /// Stopwatch used to clock the Model and Controller -> making Speed PC independent
        std::shared_ptr<singleton::Stopwatch> stopwatch;

        /**
         \n Used to transform from the [-4,4]x[-3, 3] logic of the Model
         \n to the [0,windowHeight]x[0,windowWidth] logic of the view
         */
        std::shared_ptr<singleton::Transformation> transformation;
};
} // namespace si

#endif // SPACEINVADERS_GAME_H
