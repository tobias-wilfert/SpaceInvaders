//============================================================================
// Name        : main.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Game.h"

// TODO: Push once without all the load from File to check that it works

int main()
{
        // Construct SpaceInvaders
        si::Game game = si::Game{120};
        // Start the gameLoop
        game.execute();

        return 0;
}