//============================================================================
// Name        : main.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Game.h"

int main(int argc, const char* argv[])
{
        // Get the input files
        std::deque<std::string> files;
        for (int i = 1; i < argc; ++i) {
                files.emplace_back(argv[i]);
        }

        // Construct SpaceInvaders
        si::Game game = si::Game{120, files};
        // Start the gameLoop
        game.execute();

        return 0;
}