//============================================================================
// Name        : main.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Game.h"

int main()
{
        // Construct SpaceInvaders
        si::Game game = si::Game{};
        // Start the gameLoop
        // TODO: Do error handling if needed
        game.execute();

        return 0;
}