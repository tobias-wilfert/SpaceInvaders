//============================================================================
// Name        : Level.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Level.h"

si::mvc::Level::Level()
{

        
        entity::Size size{0.16, 0.16};
        entity::Position position{0, 0};

        std::shared_ptr<entity::Enemy> e = std::make_shared<entity::Enemy>(entity::Enemy{
            size, position, 1, entity::collideObjectType::hostile, 1, entity::enemyType::a, entity::colourType::red});

        listOfEntities.push_back(e);
        listOfCollideObjects.push_back(e);
}