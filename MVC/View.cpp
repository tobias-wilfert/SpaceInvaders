//============================================================================
// Name        : View.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "View.h"
void si::mvc::View::display(sf::RenderWindow& window) const
{
        // Clear the window
        // This causes MVC to be not a clean as in Swift as we need to re draw everything even when it didn't change.
        window.clear();

        // Draw all the entities
        // Do cast if extra info is needed
        //window.draw(rect);
        //window.draw(text);

        // Display the new updated interface to the user
        window.display();
}
