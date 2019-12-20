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
        entity::Position position{-0.26f, -3.5f};
        player = std::shared_ptr<si::entity::Player>(
            new entity::Player{size, position, 1, entity::collideObjectType::friendly, 1});

        entity::Size sizeSC{2.4, 0.25};
        entity::Position positionSC{-2.85f, 3.85f};
        scoreCounter = std::shared_ptr<si::entity::Counter>(
            new entity::Counter{sizeSC, positionSC, 0, entity::counterType::score});

        entity::Size sizeCC{2.4, 0.25};
        entity::Position positionCC{-2.85f, 3.5f};
        coolDownCounter = std::shared_ptr<si::entity::Counter>(
            new entity::Counter{sizeCC, positionCC, 0, entity::counterType::cooldown});

        entity::Size sizeLC{2, 0.25};
        entity::Position positionLC{0.65f, 3.85f};
        healthCounter = std::shared_ptr<si::entity::Counter>(
            new entity::Counter{sizeLC, positionLC, 3, entity::counterType::health});

        entity::Size sizeSS{6, 2};
        entity::Position positionSS{-3, 6};
        sky = std::shared_ptr<si::entity::Immortal>(
            new entity::Immortal{sizeSS, positionSS, 1, entity::collideObjectType::hostile});

        entity::Size sizeES{6, 2};
        entity::Position positionES{-3, -4};
        earth = std::shared_ptr<si::entity::Immortal>(
            new entity::Immortal{sizeES, positionES, 1, entity::collideObjectType::friendly});
}

bool si::mvc::Model::is_interacted() const { return interacted; }

void si::mvc::Model::set_level(const std::shared_ptr<Level> & inputLevel)
{
        // Assign inputLevel to level
        Model::currentLevel = inputLevel;

        // Add all the entities from Model to level
        currentLevel->listOfEntities.push_front(sky);
        currentLevel->listOfEntities.push_front(earth);
        currentLevel->listOfEntities.push_front(player);
        currentLevel->listOfEntities.push_front(scoreCounter);
        currentLevel->listOfEntities.push_front(healthCounter);
        currentLevel->listOfEntities.push_front(coolDownCounter);

        currentLevel->listOfCollideObjects.push_back(sky);
        currentLevel->listOfCollideObjects.push_back(earth);
        currentLevel->listOfCollideObjects.push_back(player);
}

bool si::mvc::Model::is_game_over() const { return gameOver; }

bool si::mvc::Model::is_game_won() const { return gameWon; }

void si::mvc::Model::set_levels(const std::deque<std::shared_ptr<Level>>& level)
{
        levels = level;
        nextLevel();
}

void si::mvc::Model::nextLevel()
{
        if (!levels.empty()){
                auto nextLevel = levels.front();
                set_level(nextLevel);
                levels.pop_front();
        }else{
                gameWon = true;
        }
}
