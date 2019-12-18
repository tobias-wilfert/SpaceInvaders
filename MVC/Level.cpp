//============================================================================
// Name        : Level.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Level.h"

si::mvc::Level::Level()
{
        entity::Size size{0.16, 0.16};
        entity::MovePattern move_pattern{"LLDRRD", 0.25, 120};

        for (int i = 1; i < 11; ++i) {
                for (int j = 1; j < 11; ++j) {
                        entity::Position position{-3.f + i * 0.5f, -3.f + j * 0.5f};

                        std::shared_ptr<entity::Enemy> e = std::make_shared<entity::Enemy>(
                            entity::Enemy{size, position, 1, entity::collideObjectType::hostile, 1, move_pattern,
                                          entity::enemyType::a, entity::colourType::magenta});

                        listOfEntities.push_back(e);
                        listOfCollideObjects.push_back(e);
                }
        }
}