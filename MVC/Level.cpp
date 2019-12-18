//============================================================================
// Name        : Level.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Level.h"
#include "../Entity/Shield.h"

si::mvc::Level::Level()
{
        entity::Size size{0.16, 0.16};
        entity::MovePattern move_pattern{"LLDRRD", 0.25, 120};

        for (int i = 1; i < 11; ++i) {
                for (int j = 1; j < 6; ++j) {
                        entity::Position position{-3.f + i * 0.5f, 3.f - j * 0.5f};

                        std::shared_ptr<entity::Enemy> e = std::make_shared<entity::Enemy>(
                            entity::Enemy{size, position, 1, entity::collideObjectType::hostile, 1, move_pattern,
                                          entity::enemyType::a, entity::colourType::magenta});

                        listOfEntities.push_back(e);
                        listOfCollideObjects.push_back(e);
                }
        }

        entity::Size size1{0.44,0.32};
        entity::Position position1{-1,-3};

        std::shared_ptr<entity::Shield> s = std::make_shared<entity::Shield>(entity::Shield{size1,position1,1,entity::collideObjectType::passive,4});
        listOfEntities.push_back(s);
        listOfCollideObjects.push_back(s);
}