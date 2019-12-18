//============================================================================
// Name        : MoveObject.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "MoveObject.h"

si::entity::MoveObject::MoveObject(const si::entity::Size& size, const si::entity::Position& position,
    unsigned int attack_points, si::entity::collideObjectType type, int health_points,
    si::entity::MovePattern  move_pattern)
    : Mortal(size, position, attack_points, type, health_points), move_pattern(std::move(move_pattern))
{
}


void si::entity::MoveObject::move()
{
        // Check if it is time to move
        if (move_pattern.cyclesSinceLastStep >= move_pattern.moveFrequency){
                // Move
                takeStep();

                // Set the cycle count to 0
                move_pattern.cyclesSinceLastStep = 0;
        }

        // Increment the cycle count
        ++move_pattern.cyclesSinceLastStep;
}

void si::entity::MoveObject::takeStep()
{
        switch(move_pattern.pattern[move_pattern.patternIndex]){
        case 'U':
                position.y += move_pattern.stepSize;
                break;
        case 'D':
                position.y -= move_pattern.stepSize;
                break;
        case 'L':
                position.x -= move_pattern.stepSize;
                break;
        case 'R':
                position.x += move_pattern.stepSize;
                break;
        }

        // Go to next step;
        ++move_pattern.patternIndex;

        // If there is no next step jump to the start
        if (move_pattern.patternIndex >= move_pattern.pattern.size()){
                move_pattern.patternIndex = 0;
        }
}
