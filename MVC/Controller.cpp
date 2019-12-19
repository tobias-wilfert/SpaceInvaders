//============================================================================
// Name        : Controller.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Controller.h"

si::mvc::Controller::Controller(float cycles_per_second, std::shared_ptr<Model>  model)
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
                if (model->player->position.x + playerMovement <= (3 - model->player->size.width)  and !model->player->is_respawning()) {
                        // Move the player right
                        model->player->position.x += playerMovement;
                }

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                // Keep track of the time so that the player can't spam shoot
                // Check if shooting is available
                if (model->coolDownCounter->get_value() == 0) {
                        // Let the player shoot
                        // Make the bullet

                        // TODO intitialize this in the beging of the Controller
                        entity::Position position = model->player->position;
                        position.x += model->player->size.width / 2.F;
                        int health = 1;
                        unsigned int attack = 1;
                        entity::MovePattern move_pattern{"P", 0.125, 15};
                        entity::Size size{0.06, 0.12};

                        shoot(position,size,attack,health,entity::bulletType::laser, move_pattern,entity::colourType::white,true);

                        // TEST
                        if (model->player->is_respawning()){
                                model->player->set_respawning(false);
                        }

                        // Reset the counter
                        model->coolDownCounter->set_value(100);
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
        // Update the coolDown counter
        if (model->coolDownCounter->get_value() > 0) {
                model->coolDownCounter->set_value(model->coolDownCounter->get_value() - 1);

        }

        // Move all the MoveObjects
        for (const auto& ptr : model->level.listOfCollideObjects) {

                if (ptr->getEntityType() == entity::entityType::enemy) {
                        auto castPtr = std::dynamic_pointer_cast<si::entity::Enemy>(ptr);
                        castPtr->move();

                        // Check if an enemy now has a y value < -4 if yes gameOver is True
                        if (castPtr->position.y <= -4 + castPtr->size.height ){
                                model->gameOver = true;
                        }

                        if (updateCycles >= cyclesPerSecond) {
                                castPtr->set_state(!castPtr->is_state());
                        }

                } else if (ptr->getEntityType() == entity::entityType::bullet) {
                        auto castPtr = std::dynamic_pointer_cast<si::entity::Bullet>(ptr);
                        castPtr->move();
                }
        }
        // Reset the updateCycles count
        if (updateCycles >= cyclesPerSecond) {
                updateCycles = 0;
        }

        // TODO: Spawn bullets randomly for the aliens

        // Check if an CollideObeject collided with another
        // e.g Bullet with player/alien/shield/sky or ground or alien with shield/player
        for (int i = 0; i < model->level.listOfCollideObjects.size(); ++i) {
                auto entity = model->level.listOfCollideObjects.front();
                model->level.listOfCollideObjects.pop_front();
                for (const auto& obj : model->level.listOfCollideObjects) {
                        entity::checkCollision(entity, obj);
                }
                model->level.listOfCollideObjects.push_back(entity);
        }

        // Check what the player is doing
        checkPlayer();

        // Delete all dead CollideObjects from the list
        for (int i = 0; i < model->level.listOfCollideObjects.size(); ++i) {
                auto front = model->level.listOfCollideObjects.front();
                model->level.listOfCollideObjects.pop_front();

                if (!front->is_destroyed()) {
                        model->level.listOfCollideObjects.push_back(front);
                }else{
                        // If an enemy died
                        if (front->getEntityType() == entity::entityType::enemy){
                                auto castPtr = std::dynamic_pointer_cast<si::entity::Enemy>(front);

                                // TODO: Make more elegant Maybe to easy? should consider a
                                int value = 10;
                                model->scoreCounter->set_value(model->scoreCounter->get_value() + value);
                        }

                }
        }

        // Delete all dead entities from the list
        for (int i = 0; i < model->level.listOfEntities.size(); ++i) {
                auto entity = model->level.listOfEntities.front();
                model->level.listOfEntities.pop_front();

                // Check that it is a collide object
                if (entity->getEntityType() != entity::entityType::counter) {
                        if (!std::dynamic_pointer_cast<entity::CollideObject>(entity)->is_destroyed()) {
                                model->level.listOfEntities.push_back(entity);
                        }
                } else {
                        model->level.listOfEntities.push_back(entity);
                }
        }

        // Increment the cycleCount
        ++updateCycles;
}

void si::mvc::Controller::checkPlayer() const
{
        // Check if the player is currently respawning
        if (model->player->is_respawning()){
                // If player got hit while respawning ignore
                model->player->set_destroyed(false);

        }else{
                // Check if the player got hit
                if (model->player->is_destroyed()){
                        // Check if we have a backup life
                        if ( model->healthCounter->get_value() >= 1){
                                model->player->set_destroyed(false);
                                model->player->set_respawning(true);
                                model->healthCounter->set_value(model->healthCounter->get_value()-1);
                        }else{
                                // The player died for good
                                model->gameOver = true;
                        }
                }
        }

}

void si::mvc::Controller::shoot(si::entity::Position origin, si::entity::Size size, unsigned int attack, int health,
    si::entity::bulletType bullet_type, si::entity::MovePattern move_pattern, entity::colourType colour_type,
    bool fromPlayer) const
{
        entity::collideObjectType collide_object_type;
        entity::Position position{origin.x - size.width / 2.f, origin.y};

        if (fromPlayer) {
                collide_object_type = entity::collideObjectType::friendly;
                move_pattern.pattern = "U";
                position.y += size.height;
        } else {
                collide_object_type = entity::collideObjectType::hostile;
                move_pattern.pattern = "D";
                position.y -= size.height;
        }

        addBulletToGame(entity::Bullet{
            size, position, attack, collide_object_type, health, move_pattern, bullet_type, colour_type});
}

void si::mvc::Controller::addBulletToGame(si::entity::Bullet bullet) const
{
        std::shared_ptr<entity::Bullet> bulletPrt = std::make_shared<entity::Bullet>(bullet);
        model->level.listOfCollideObjects.push_back(bulletPrt);
        model->level.listOfEntities.push_back(bulletPrt);
        model->level.listOfBullets.push_back(bulletPrt);
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
void si::mvc::Controller::handleGameOverScreenInput(sf::RenderWindow& window) const
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
