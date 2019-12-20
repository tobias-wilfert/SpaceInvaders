//============================================================================
// Name        : Level.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Level.h"

bool si::mvc::Level::is_level_complete() const
{
        for (const auto& ptr : listOfEntities) {
                if (ptr->getEntityType() == entity::entityType::enemy) {
                        return false;
                }
        }

        return true;
}
void si::mvc::Level::addObject(std::shared_ptr<entity::CollideObject> objPtr)
{
        listOfEntities.push_back(objPtr);
        listOfCollideObjects.push_back(objPtr);
}
