//============================================================================
// Name        : Paser.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_PARSER_H
#define SPACEINVADERS_PARSER_H

#include <cstring>
#include <memory>
#include <iostream>

#include "tinyxml.h"
#include "../MVC/Level.h"

/// Namespace of SpaceInvaders
namespace si {

class Parser
{
public:

        // TODO Comment
        std::shared_ptr<mvc::Level> parseFile(const std::string& pathToFile);

private:

        bool isValidFile(TiXmlDocument& file, const std::string& pathToFile) const;

        void parseLevel(TiXmlDocument& file, const std::shared_ptr<mvc::Level>& levelPtr);

        si::entity::MovePattern parseMovePattern(TiXmlElement* movePattern) const;

        entity::Position parsePosition(TiXmlElement* positionPtr) const;

        entity::Size parseSize(TiXmlElement* sizePtr) const;

        entity::Enemy parseEnemy(TiXmlElement* enemyPtr) const;

        std::deque<si::entity::MovePattern> move_patterns;

        entity::Shield parseShield(TiXmlElement* shieldPtr) const;

        entity::enemyType parseEnemyType(TiXmlElement* typePtr) const;

        entity::colourType parseColourType(TiXmlElement* colourPtr) const;
};

} // namespace si

#endif // SPACEINVADERS_PARSER_H
