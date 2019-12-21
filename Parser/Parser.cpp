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
                exit(2);
        }

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

        // Clear the move_patterns
        move_patterns.clear();

        for (TiXmlElement* currentElem = root->FirstChildElement(); currentElem != nullptr;
             currentElem = currentElem->NextSiblingElement()) {
                // Make a vector of move Object for aliens to reference
                if (currentElem->ValueTStr() == "MovePatterns") {
                        // Parse the move objects
                        for (TiXmlElement* moveObj = currentElem->FirstChildElement(); moveObj != nullptr;
                             moveObj = moveObj->NextSiblingElement()) {
                                try {
                                        move_patterns.push_back(parseMovePattern(moveObj));
                                } catch (const std::exception& e) {
                                        std::cerr << "Failed to parse movePattern from" << std::endl;
                                        std::cerr << e.what() << std::endl;
                                        exit(2);
                                }
                        }
                }

                // Parse all the enemies
                if (currentElem->ValueTStr() == "Enemies") {
                        // Parse the enemy
                        for (TiXmlElement* enemyObj = currentElem->FirstChildElement(); enemyObj != nullptr;
                             enemyObj = enemyObj->NextSiblingElement()) {
                                try {
                                        levelPtr->addObject(std::make_shared<entity::Enemy>(parseEnemy(enemyObj)));
                                } catch (const std::exception& e) {
                                        std::cerr << "Unable to parse enemy properly" << std::endl;
                                        std::cerr << e.what() << std::endl;
                                }
                        }
                }

                // Parse all the shields
                if (currentElem->ValueTStr() == "Shields") {
                        for (TiXmlElement* shieldObj = currentElem->FirstChildElement(); shieldObj != nullptr;
                             shieldObj = shieldObj->NextSiblingElement()) {
                                try {
                                        levelPtr->addObject(std::make_shared<entity::Shield>(parseShield(shieldObj)));
                                } catch (const std::exception& e) {
                                        std::cerr << "Unable to parse shield properly" << std::endl;
                                        std::cerr << e.what() << std::endl;
                                }
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
                if (attr->ValueTStr() == "pattern") {
                        if (attr->GetText() == nullptr) {
                                std::cerr << "Value of " << attr->Value() << " is empty." << std::endl;
                        } else {
                                pattern = attr->GetText();
                        }
                }
                if (attr->ValueTStr() == "stepSize") {
                        if (attr->GetText() == nullptr) {
                                std::cerr << "Value of " << attr->Value() << " is empty." << std::endl;
                        } else {
                                stepSize = std::stof(attr->GetText());
                        }
                }
                if (attr->ValueTStr() == "moveFrequency") {
                        if (attr->GetText() == nullptr) {
                                std::cerr << "Value of " << attr->Value() << " is empty." << std::endl;
                        } else {
                                moveFrequency = std::stof(attr->GetText());
                        }
                }
        }

        return si::entity::MovePattern{pattern, stepSize, moveFrequency};
}

si::entity::Position si::Parser::parsePosition(TiXmlElement* positionPtr) const
{
        float x{0}, y{0};

        for (TiXmlElement* attr = positionPtr->FirstChildElement(); attr != nullptr;
             attr = attr->NextSiblingElement()) {
                if (attr->ValueTStr() == "x") {
                        if (attr->GetText() == nullptr) {
                                std::cerr << "Value of " << attr->Value() << " is empty." << std::endl;
                        } else {
                                x = std::stof(attr->GetText());
                        }
                }

                if (attr->ValueTStr() == "y") {
                        if (attr->GetText() == nullptr) {
                                std::cerr << "Value of " << attr->Value() << " is empty." << std::endl;
                        } else {
                                y = std::stof(attr->GetText());
                        }
                }
        }
        return si::entity::Position{x, y};
}

si::entity::Size si::Parser::parseSize(TiXmlElement* sizePtr) const
{
        float width{0}, height{0};

        for (TiXmlElement* attr = sizePtr->FirstChildElement(); attr != nullptr; attr = attr->NextSiblingElement()) {
                if (attr->ValueTStr() == "width") {
                        if (attr->GetText() == nullptr) {
                                std::cerr << "Value of " << attr->Value() << " is empty." << std::endl;
                        } else {
                                width = std::stof(attr->GetText());
                        }
                }

                if (attr->ValueTStr() == "height") {
                        if (attr->GetText() == nullptr) {
                                std::cerr << "Value of " << attr->Value() << " is empty." << std::endl;
                        } else {
                                height = std::stof(attr->GetText());
                        }
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
                if (attr->ValueTStr() == "size") {
                        size = parseSize(attr);
                } else if (attr->ValueTStr() == "position") {
                        position = parsePosition(attr);
                } else if (attr->ValueTStr() == "attackPoints") {
                        if (attr->GetText() == nullptr) {
                                std::cerr << "Value of " << attr->Value() << " is empty." << std::endl;
                        } else {
                                attack_points = static_cast<unsigned int>(std::stoi(attr->GetText()));
                        }
                } else if (attr->ValueTStr() == "healthPoints") {
                        if (attr->GetText() == nullptr) {
                                std::cerr << "Value of " << attr->Value() << " is empty." << std::endl;
                        } else {
                                health_points = std::stoi(attr->GetText());
                        }
                } else if (attr->ValueTStr() == "movePattern") {
                        if (attr->GetText() == nullptr) {
                                std::cerr << "Value of " << attr->Value() << " is empty." << std::endl;
                        } else {
                                move_pattern = move_patterns[std::stoi(attr->GetText())];
                        }
                } else if (attr->ValueTStr() == "enemyType") {
                        enemy_type = parseEnemyType(attr);
                } else if (attr->ValueTStr() == "colour") {
                        colour_type = parseColourType(attr);
                }
        }

        return si::entity::Enemy{size,          position,     attack_points, collide_object_type,
                                 health_points, move_pattern, enemy_type,    colour_type};
}

si::entity::enemyType si::Parser::parseEnemyType(TiXmlElement* typePtr) const
{
        entity::enemyType enemy_type = entity::enemyType::a;
        std::string text;

        if (typePtr->GetText() == nullptr) {
                std::cerr << "Value of " << typePtr->Value() << " is empty." << std::endl;
        } else {
                text = typePtr->GetText();
        }

        if (text == "a") {
                enemy_type = entity::enemyType::a;
        } else if (text == "b") {
                enemy_type = entity::enemyType::b;
        } else if (text == "c") {
                enemy_type = entity::enemyType::c;
        } else if (text == "m") {
                enemy_type = entity::enemyType::m;
        }
        return enemy_type;
}

si::entity::colourType si::Parser::parseColourType(TiXmlElement* colourPtr) const
{
        entity::colourType colour_type = entity::colourType::white;
        std::string colour;

        if (colourPtr->GetText() == nullptr) {
                std::cerr << "Value of " << colourPtr->Value() << " is empty." << std::endl;
        } else {
                colour = colourPtr->GetText();
        }

        if (colour == "white") {
                colour_type = entity::colourType::white;
        } else if (colour == "red") {
                colour_type = entity::colourType::red;
        } else if (colour == "green") {
                colour_type = entity::colourType::green;
        } else if (colour == "blue") {
                colour_type = entity::colourType::blue;
        } else if (colour == "yellow") {
                colour_type = entity::colourType::yellow;
        } else if (colour == "magenta") {
                colour_type = entity::colourType::magenta;
        } else if (colour == "cyan") {
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
                if (attr->ValueTStr() == "size") {
                        size = parseSize(attr);
                } else if (attr->ValueTStr() == "position") {
                        position = parsePosition(attr);
                } else if (attr->ValueTStr() == "attackPoints") {
                        if (attr->GetText() == nullptr) {
                                std::cerr << "Value of " << attr->Value() << " is empty." << std::endl;
                        } else {
                                attack_points = static_cast<unsigned int>(std::stoi(attr->GetText()));
                        }
                } else if (attr->ValueTStr() == "healthPoints") {
                        if (attr->GetText() == nullptr) {
                                std::cerr << "Value of " << attr->Value() << " is empty." << std::endl;
                        } else {
                                health_points = std::stoi(attr->GetText());
                        }
                }
        }

        return si::entity::Shield{size, position, attack_points, collide_object_type, health_points};
}
