//============================================================================
// Name        : Parser.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Parser.h"
std::shared_ptr<si::mvc::Level> si::Parser::parseFile(const std::string& pathToFile)
{
        // Make the pointer to the level
        std::shared_ptr<si::mvc::Level> levelPtr = std::make_shared<si::mvc::Level>(mvc::Level{});
        TiXmlDocument document;

        // Check if the file is valid -> van be parsed
        if (!isValidFile(document, pathToFile)) {
                exit(0);
        }

        // TODO Catch errors here for stoi and stof and getText
        // Parse the level information from the file
        parseLevel(document, levelPtr);

        // Return the pointer to the level
        document.Clear();
        return levelPtr;
}

bool si::Parser::isValidFile(TiXmlDocument& file, const std::string& pathToFile) const
{
        // Load the file
        if (!file.LoadFile(pathToFile.c_str())) {
                std::cerr << file.ErrorDesc() << std::endl;
                std::cerr << "Error in document row: " << file.ErrorRow() << std::endl;
                std::cerr << "Could not load file at: " << pathToFile << std::endl;
                return false;
        }

        // Check if we can get an root element
        TiXmlElement* root = file.FirstChildElement();
        if (root == nullptr) {
                std::cerr << "Failed to load file: No root element." << std::endl;
                file.Clear();
                return false;
        }
        return true;
}

void si::Parser::parseLevel(TiXmlDocument& file, const std::shared_ptr<mvc::Level>& levelPtr)
{
        // Get the root of the file
        TiXmlElement* root = file.FirstChildElement();

        for (TiXmlElement* currentElem = root->FirstChildElement(); currentElem != nullptr;
             currentElem = currentElem->NextSiblingElement()) {
                // Make a vector of move Object for aliens to referenace
                if (std::strcmp(currentElem->Value(), "MovePatterns") == 0) {
                        // Parse the move objects
                        for (TiXmlElement* moveObj = currentElem->FirstChildElement(); moveObj != nullptr;
                             moveObj = moveObj->NextSiblingElement()) {
                                move_patterns.push_back(parseMovePattern(moveObj));
                        }
                }

                // Parse all the enemies
                if (std::strcmp(currentElem->Value(), "Enemies") == 0) {
                        // Parse the enemy
                        for (TiXmlElement* enemyObj = currentElem->FirstChildElement(); enemyObj != nullptr;
                             enemyObj = enemyObj->NextSiblingElement()) {
                                levelPtr->addObject(std::make_shared<entity::Enemy>(parseEnemy(enemyObj)));
                        }
                }

                // Parse all the shields
                if (std::strcmp(currentElem->Value(), "Shields") == 0) {
                        for (TiXmlElement* shieldObj = currentElem->FirstChildElement(); shieldObj != nullptr;
                             shieldObj = shieldObj->NextSiblingElement()) {
                                levelPtr->addObject(std::make_shared<entity::Shield>(parseShield(shieldObj)));
                        }
                }
        }
}

si::entity::MovePattern si::Parser::parseMovePattern(TiXmlElement* movePattern) const
{

        std::string pattern = "N";
        float stepSize{0}, moveFrequency{0};

        for (TiXmlElement* attr = movePattern->FirstChildElement(); attr != nullptr;
             attr = attr->NextSiblingElement()) {
                if (std::strcmp(attr->Value(), "pattern") == 0) {
                        pattern = attr->GetText();
                }
                if (std::strcmp(attr->Value(), "stepSize") == 0) {
                        stepSize = std::stof(attr->GetText());
                }
                if (std::strcmp(attr->Value(), "moveFrequency") == 0) {
                        moveFrequency = std::stof(attr->GetText());
                }
        }

        return si::entity::MovePattern{pattern, stepSize, moveFrequency};
        ;
}

si::entity::Position si::Parser::parsePosition(TiXmlElement* positionPtr) const
{
        float x{0}, y{0};

        for (TiXmlElement* attr = positionPtr->FirstChildElement(); attr != nullptr;
             attr = attr->NextSiblingElement()) {
                if (std::strcmp(attr->Value(), "x") == 0) {
                        x = std::stof(attr->GetText());
                }

                if (std::strcmp(attr->Value(), "y") == 0) {
                        y = std::stof(attr->GetText());
                }
        }
        return si::entity::Position{x, y};
        ;
}

si::entity::Size si::Parser::parseSize(TiXmlElement* sizePtr) const
{
        float width{0}, height{0};

        for (TiXmlElement* attr = sizePtr->FirstChildElement(); attr != nullptr; attr = attr->NextSiblingElement()) {
                if (std::strcmp(attr->Value(), "width") == 0) {
                        width = std::stof(attr->GetText());
                }

                if (std::strcmp(attr->Value(), "height") == 0) {
                        height = std::stof(attr->GetText());
                }
        }

        return si::entity::Size{width, height};
}

si::entity::Enemy si::Parser::parseEnemy(TiXmlElement* enemyPtr) const
{
        entity::Size size{0, 0};
        entity::Position position{0, 0};
        unsigned int attack_points{0};
        entity::collideObjectType collide_object_type{entity::collideObjectType::hostile};
        int health_points{0};
        entity::MovePattern move_pattern{"N", 0, 0};
        entity::enemyType enemy_type{entity::enemyType::a};
        entity::colourType colour_type{entity::colourType::white};

        for (TiXmlElement* attr = enemyPtr->FirstChildElement(); attr != nullptr; attr = attr->NextSiblingElement()) {
                if (std::strcmp(attr->Value(), "size") == 0) {
                        size = parseSize(attr);
                } else if (std::strcmp(attr->Value(), "position") == 0) {
                        position = parsePosition(attr);
                } else if (std::strcmp(attr->Value(), "attackPoints") == 0) {
                        attack_points = std::stoi(attr->GetText());
                } else if (std::strcmp(attr->Value(), "healthPoints") == 0) {
                        health_points = std::stoi(attr->GetText());
                } else if (std::strcmp(attr->Value(), "movePattern") == 0) {
                        move_pattern = move_patterns[std::stoi(attr->GetText())];
                } else if (std::strcmp(attr->Value(), "enemyType") == 0) {
                        enemy_type = parseEnemyType(attr);
                } else if (std::strcmp(attr->Value(), "colour") == 0) {
                        colour_type = parseColourType(attr);
                }
        }

        return si::entity::Enemy{size,          position,     attack_points, collide_object_type,
                                 health_points, move_pattern, enemy_type,    colour_type};
}

si::entity::enemyType si::Parser::parseEnemyType(TiXmlElement* typePtr) const
{
        entity::enemyType enemy_type = entity::enemyType::a;

        if (std::strcmp(typePtr->GetText(), "a") == 0) {
                enemy_type = entity::enemyType::a;
        } else if (std::strcmp(typePtr->GetText(), "b") == 0) {
                enemy_type = entity::enemyType::b;
        } else if (std::strcmp(typePtr->GetText(), "c") == 0) {
                enemy_type = entity::enemyType::c;
        } else if (std::strcmp(typePtr->GetText(), "m") == 0) {
                enemy_type = entity::enemyType::m;
        }
        return enemy_type;
}

si::entity::colourType si::Parser::parseColourType(TiXmlElement* colourPtr) const
{
        entity::colourType colour_type = entity::colourType::white;

        if (std::strcmp(colourPtr->GetText(), "white") == 0) {
                colour_type = entity::colourType::white;
        } else if (std::strcmp(colourPtr->GetText(), "red") == 0) {
                colour_type = entity::colourType::red;
        } else if (std::strcmp(colourPtr->GetText(), "green") == 0) {
                colour_type = entity::colourType::green;
        } else if (std::strcmp(colourPtr->GetText(), "blue") == 0) {
                colour_type = entity::colourType::blue;
        } else if (std::strcmp(colourPtr->GetText(), "yellow") == 0) {
                colour_type = entity::colourType::yellow;
        } else if (std::strcmp(colourPtr->GetText(), "magenta") == 0) {
                colour_type = entity::colourType::magenta;
        } else if (std::strcmp(colourPtr->GetText(), "cyan") == 0) {
                colour_type = entity::colourType::cyan;
        }

        return colour_type;
}
si::entity::Shield si::Parser::parseShield(TiXmlElement* shieldPtr) const
{
        entity::Size size{0, 0};
        entity::Position position{0, 0};
        unsigned int attack_points{0};
        entity::collideObjectType collide_object_type{entity::collideObjectType::passive};
        int health_points{0};

        for (TiXmlElement* attr = shieldPtr->FirstChildElement(); attr != nullptr; attr = attr->NextSiblingElement()) {
                if (std::strcmp(attr->Value(), "size") == 0) {
                        size = parseSize(attr);
                } else if (std::strcmp(attr->Value(), "position") == 0) {
                        position = parsePosition(attr);
                } else if (std::strcmp(attr->Value(), "attackPoints") == 0) {
                        attack_points = std::stoi(attr->GetText());
                } else if (std::strcmp(attr->Value(), "healthPoints") == 0) {
                        health_points = std::stoi(attr->GetText());
                }
        }

        return si::entity::Shield{size, position, attack_points, collide_object_type, health_points};
}
