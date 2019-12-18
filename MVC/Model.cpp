//============================================================================
// Name        : Model.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Model.h"
si::mvc::Model::Model()
{
        // Initialize all the level independent entities

        entity::Size size{0.26, 0.16};
        entity::Position position{-0.26, 3.5};
        player = std::shared_ptr<si::entity::Player>(
            new entity::Player{size, position, 1, entity::collideObjectType::friendly, 1});

        entity::Size sizeSC{2.4, 0.25};
        entity::Position positionSC{-2.85, -3.85};
        scoreCounter = std::shared_ptr<si::entity::Counter>(
            new entity::Counter{sizeSC, positionSC, 0, entity::counterType::score});

        entity::Size sizeCC{2.4, 0.25};
        entity::Position positionCC{-2.85, -3.5};
        coolDownCounter = std::shared_ptr<si::entity::Counter>(
            new entity::Counter{sizeCC, positionCC, 0, entity::counterType::cooldown});

        entity::Size sizeLC{2, 0.25};
        entity::Position positionLC{0.65, -3.85};
        healthCounter = std::shared_ptr<si::entity::Counter>(
            new entity::Counter{sizeLC, positionLC, 3, entity::counterType::health});

        entity::Size sizeSS{6, 2};
        entity::Position positionSS{-3, -6};
        sky = std::shared_ptr<si::entity::Immortal>(
            new entity::Immortal{sizeSS, positionSS, 1, entity::collideObjectType::hostile});

        entity::Size sizeES{6, 2};
        entity::Position positionES{-3, 4};
        earth = std::shared_ptr<si::entity::Immortal>(
            new entity::Immortal{sizeES, positionES, 1, entity::collideObjectType::friendly});
}

bool si::mvc::Model::is_interacted() const { return interacted; }

void si::mvc::Model::set_level(const Level& inputLevel)
{
        // Assign inputLevel to level
        Model::level = inputLevel;

        // Add all the entities from Model to level
        level.listOfEntities.push_front(sky);
        level.listOfEntities.push_front(earth);
        level.listOfEntities.push_front(player);
        level.listOfEntities.push_front(scoreCounter);
        level.listOfEntities.push_front(healthCounter);
        level.listOfEntities.push_front(coolDownCounter);
}
