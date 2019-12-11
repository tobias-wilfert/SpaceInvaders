//============================================================================
// Name        : main.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Game.h"

// TODO: Think about if Google tests are worth it

int main()
{
        // Construct SpaceInvaders
        Game game = Game{};
        // Start the gameLoop
        // TODO: Do error handling if needed
        game.execute();

        return 0;
}