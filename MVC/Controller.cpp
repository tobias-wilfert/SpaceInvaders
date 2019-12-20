//============================================================================
// Name        : Controller.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Controller.h"

si::mvc::Controller::Controller(float cycles_per_second, std::shared_ptr<Model> model)
    : cyclesPerSecond(cycles_per_second), model(std::move(model))
{
}

void si::mvc::Controller::handleInput(sf::RenderWindow& window) const
{
        // Handle all events
        handelEvent(window);

        // Handle game input
        float playerMovement = model->playerMovementSpeed / cyclesPerSecond;

        // Moving is only allowed when player is not respawning
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                // Check that move is legal -> The player doesn't move from the screen
                if (model->player->position.x - playerMovement >= -3 and !model->player->is_respawning()) {
                        // Move the player left
                        model->player->position.x -= playerMovement;
                }

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                // Check that move is legal -> The player doesn't move from the screen
                if (model->player->position.x + playerMovement <= (3 - model->player->size.width) and
                    !model->player->is_respawning()) {
                        // Move the player right
                        model->player->position.x += playerMovement;
                }

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                // Check if shooting is available
                if (model->coolDownCounter->get_value() == 0) {
                        // Let the player shoot
                        playerShoot();

                        if (model->player->is_respawning()) {
                                model->player->set_respawning(false);
                        }
                        // Reset the counter
                        model->coolDownCounter->set_value(shootFrequency);
                }
        }
}

void si::mvc::Controller::handleTitleScreenInput(sf::RenderWindow& window) const
{
        // Check if the player presses a key
        sf::Event event{};
        while (window.pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                        window.close();
                        exit(0);
                case sf::Event::KeyPressed:
                        model->interacted = true;
                default:
                        break;
                }
        }
}
void si::mvc::Controller::updateModel()
{
        // Check if there are any Enemies left in the level
        if (model->currentLevel->is_level_complete()) {
                model->nextLevel();
        }

        // Update the coolDown counter
        if (model->coolDownCounter->get_value() > 0) {
                model->coolDownCounter->set_value(model->coolDownCounter->get_value() - 1);
        }

        // Move all the MoveObjects and spawn enemy bullets
        moveObjects();

        // Check if an CollideObject collided with another
        checkCollisions();

        // Check what the player is doing
        checkPlayer();

        // Delete all dead CollideObjects
        cleanUpCollideObjects();

        //  Delete all the dead bullets
        cleanUpBullets();

        // Delete all dead entities
        cleanUpEntities();

        // Reset the updateCycles count
        if (updateCycles >= static_cast<int>(cyclesPerSecond)) {
                updateCycles = 0;
        }

        // Increment the cycleCount
        ++updateCycles;
}

void si::mvc::Controller::checkPlayer() const
{
        // Check if the player is currently respawning
        if (model->player->is_respawning()) {
                // If player got hit while respawning ignore
                model->player->set_destroyed(false);

        } else {
                // Check if the player got hit
                if (model->player->is_destroyed()) {
                        // Check if we have a backup life
                        if (model->healthCounter->get_value() >= 1) {
                                model->player->set_destroyed(false);
                                model->player->set_respawning(true);
                                model->healthCounter->set_value(model->healthCounter->get_value() - 1);
                        } else {
                                // The player died for good
                                model->gameOver = true;
                        }
                }
        }
}

void si::mvc::Controller::addBulletToGame(si::entity::Bullet bullet) const
{
        std::shared_ptr<entity::Bullet> bulletPrt = std::make_shared<entity::Bullet>(bullet);
        model->currentLevel->listOfCollideObjects.push_back(bulletPrt);
        model->currentLevel->listOfEntities.push_back(bulletPrt);
        model->currentLevel->listOfBullets.push_back(bulletPrt);
}

void si::mvc::Controller::handelEvent(sf::RenderWindow& window) const
{
        sf::Event event{};

        while (window.pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                        window.close();
                        break;
                        // Place to add extra Handles if needed.
                default:
                        break;
                }
        }
}

void si::mvc::Controller::handleGameEndScreenInput(sf::RenderWindow& window) const
{
        sf::Event event{};

        while (window.pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                        window.close();
                        exit(0);
                        // Place to add extra Handles if needed.
                default:
                        break;
                }
        }
}

void si::mvc::Controller::playerShoot() const
{
        // Make the bullet
        int health = 1;
        unsigned int attack = 1;
        entity::Size size{0.06, 0.12};
        entity::MovePattern move_pattern{"U", 0.125, 15};
        entity::Position position = model->player->position;
        position.x += model->player->size.width / 2.f - size.width / 2.f;
        position.y += size.height;

        // Add the bullet
        addBulletToGame(entity::Bullet{size, position, attack, entity::collideObjectType::friendly, health,
                                       move_pattern, entity::bulletType::laser, entity::colourType::white});
}

void si::mvc::Controller::alienShoot(const std::shared_ptr<si::entity::Enemy>& enemy) const
{
        // Make the bullet
        int health = 1;
        unsigned int attack = 1;
        entity::Size size{0.06, 0.12};
        entity::MovePattern move_pattern{"D", 0.125, 15};
        entity::Position position = enemy->position;
        position.x += enemy->size.width / 2.f - size.width / 2.f;
        position.y -= size.height;

        // add the bullet
        addBulletToGame(entity::Bullet{size, position, attack, entity::collideObjectType::hostile, health, move_pattern,
                                       entity::bulletType::down, enemy->get_colour()});
}
void si::mvc::Controller::moveObjects()
{
        // Ruff amount of aliens
        unsigned long amountOfAliens = model->currentLevel->listOfCollideObjects.size() - model->currentLevel->listOfBullets.size() - 3;
        // Create a random number
        int counter{0};
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> uni(0, static_cast<int>(amountOfAliens));
        auto random_integer = uni(rng);

        // Loop over all the objects
        for (const auto& objectPtr : model->currentLevel->listOfCollideObjects) {
                // If the object is an enemy
                if (objectPtr->getEntityType() == entity::entityType::enemy) {
                        auto castPtr = std::dynamic_pointer_cast<si::entity::Enemy>(objectPtr);
                        castPtr->move();

                        // Check if an enemy now has a y value < -4 if yes gameOver is True
                        if (castPtr->position.y <= -4 + castPtr->size.height) {
                                model->gameOver = true;
                        }
                        // Check if the alien needs to change state/ shoot a bulet
                        if (updateCycles >= static_cast<int>(cyclesPerSecond)) {
                                castPtr->set_state(!castPtr->is_state());

                                // If the enemy should shoot a bullet
                                if (counter == random_integer) {
                                        alienShoot(castPtr);
                                }
                        }
                        // increment the counter
                        ++counter;

                } else if (objectPtr->getEntityType() == entity::entityType::bullet) {
                        auto castPtr = std::dynamic_pointer_cast<si::entity::Bullet>(objectPtr);
                        castPtr->move();
                }
        }
}

void si::mvc::Controller::checkCollisions() const
{
        for (const auto& objectPtr : model->currentLevel->listOfCollideObjects) {
                for (const auto& objectPtr2 : model->currentLevel->listOfCollideObjects) {
                        entity::checkCollision(objectPtr, objectPtr2);
                }
        }
}

void si::mvc::Controller::cleanUpBullets() const
{
        for (unsigned int i = 0; i < model->currentLevel->listOfBullets.size(); ++i) {
                auto bullet = model->currentLevel->listOfBullets.front();
                model->currentLevel->listOfBullets.pop_front();

                if (!bullet->is_destroyed()) {
                        model->currentLevel->listOfBullets.push_back(bullet);
                }
        }
}

void si::mvc::Controller::cleanUpCollideObjects() const
{
        for (unsigned int i = 0; i < model->currentLevel->listOfCollideObjects.size(); ++i) {
                auto objectPtr = model->currentLevel->listOfCollideObjects.front();
                model->currentLevel->listOfCollideObjects.pop_front();

                if (!objectPtr->is_destroyed()) {
                        model->currentLevel->listOfCollideObjects.push_back(objectPtr);
                } else {
                        // If an enemy died
                        if (objectPtr->getEntityType() == entity::entityType::enemy) {
                                updateScore(std::dynamic_pointer_cast<si::entity::Enemy>(objectPtr));
                        }
                }
        }
}

void si::mvc::Controller::updateScore(const std::shared_ptr<entity::Enemy>& enemy) const
{
        int value{0};
        switch (enemy->get_enemy_type()) {
        case entity::enemyType::a:
                value = 400;
                break;
        case entity::enemyType::b:
                value = 200;
                break;
        case entity::enemyType::c:
                value = 100;
                break;
        case entity::enemyType::m:
                value = 10000;
                break;
        }

        // Update the score
        model->scoreCounter->set_value(model->scoreCounter->get_value() + value);
}

void si::mvc::Controller::cleanUpEntities() const
{
        for (unsigned int i = 0; i < model->currentLevel->listOfEntities.size(); ++i) {
                auto entity = model->currentLevel->listOfEntities.front();
                model->currentLevel->listOfEntities.pop_front();

                // Check that it is a collide object
                if (entity->getEntityType() != entity::entityType::counter) {
                        if (!std::dynamic_pointer_cast<entity::CollideObject>(entity)->is_destroyed()) {
                                model->currentLevel->listOfEntities.push_back(entity);
                        }
                } else {
                        model->currentLevel->listOfEntities.push_back(entity);
                }
        }
}
