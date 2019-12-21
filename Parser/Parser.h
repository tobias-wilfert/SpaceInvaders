//============================================================================
// Name        : Paser.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_PARSER_H
#define SPACEINVADERS_PARSER_H

#include <cstring>
#include <iostream>
#include <memory>

#include "../MVC/Level.h"
#include "tinyxml.h"

/// Namespace of SpaceInvaders
namespace si {

/**
 * Parser to parse all information needed to make a Level from an xml file
 */
class Parser
{
public:

        /**
         \n Make a level from the specifications provided in the file ar pathTofile
         \n @param pathToFile Path to the xml file that contains the level specifications for the Level
         \n @return A pointer to an Level object
         */
        std::shared_ptr<mvc::Level> parseFile(const std::string& pathToFile);

private:

        /// List of all the movePatterns parsed from the xml file for enemies in xml to reference
        std::deque<si::entity::MovePattern> move_patterns;

        /**
         \n Check if a file is valid ( load the file and check if it has a root element)
         \n @param file TinXmlDocument representation of the xml File
         \n @param pathToFile Path to the xml file
         \n @return True if the file can be loaded and has a root element
         */
        bool isValidFile(TiXmlDocument& file, const std::string& pathToFile) const;

        /**
         \n Parse a Level from the file
         \n @param file The file to parse the level from
         \n @param levelPtr Pointer to the level that should be parsed to
         */
        void parseLevel(TiXmlDocument& file, const std::shared_ptr<mvc::Level>& levelPtr);

        /**
         \n Parse a move pattern from movePattern
         \n @param movePattern Pointer to an xml tag that has all the sub tags to describe a movePattern
         \n @return A move pattern with the specifications from movePattern
         */
        si::entity::MovePattern parseMovePattern(TiXmlElement* movePattern) const;

        /**
         \n Parse a position from positionPtr
         \n @param positionPtr Pointer to an xml tag that has all the sub tag to describe a position
         \n @return A position with the specifications from positionPtr
         */
        entity::Position parsePosition(TiXmlElement* positionPtr) const;

        /**
         \n Parse a size from sizePtr
         \n @param sizePtr Pointer to an xml tag that has all the sub tag to describe a size
         \n @return A size with the specifications from sizePtr
         */
        entity::Size parseSize(TiXmlElement* sizePtr) const;

        /**
         \n Parse an enemy from enemyPtr
         \n @param enemyPtr Pointer to an xml tag that has all the sub tags to describe an enemy
         \n @return An enemy with the specifications from enemyPtr
         */
        entity::Enemy parseEnemy(TiXmlElement* enemyPtr) const;

        /**
         \n Parse a shield from shieldPtr
         \n @param shieldPtr Pointer to an xml tag that has all the sub tags to describe an shield
         \n @return A shield with the specifications from enemyPtr
         */
        entity::Shield parseShield(TiXmlElement* shieldPtr) const;

        /**
         \n Parse an enemyType from typePtr
         \n @param typePtr Pointer to  an xml tag that describes an enemy type
         \n @return An enemy with the specifications from typePtr
         */
        entity::enemyType parseEnemyType(TiXmlElement* typePtr) const;

        /**
         \n Parse a colour from colourPtr
         \n @param colourPtr Pointer to an xml tag that describes a colour
         \n @return A colour with the specifications from colourPtr
         */
        entity::colourType parseColourType(TiXmlElement* colourPtr) const;
};

} // namespace si

#endif // SPACEINVADERS_PARSER_H
