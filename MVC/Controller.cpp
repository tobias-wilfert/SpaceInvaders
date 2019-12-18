//============================================================================
// Name        : Controller.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Controller.h"

#include <utility>

si::mvc::Controller::Controller(float cycles_per_second, const std::shared_ptr<Model>& model)
    : cyclesPerSecond(cycles_per_second), model(model)
{
}

void si::mvc::Controller::handleInput(sf::RenderWindow& window) const
{
        // Handle all events
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

        // Handle game input
        float playerMovement = model->playerMovementSpeed/cyclesPerSecond;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                // Check that move is legal -> The player doesn't move from the screen
                if (model->player->position.x - playerMovement >= -3) {
                        // Move the player left
                        model->player->position.x -= playerMovement;
                }

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                // Check that move is legal
                if (model->player->position.x + playerMovement <= (3 - model->player->size.width)) {
                        // Move the player right
                        model->player->position.x += playerMovement;
                }

        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                // Keep track of the time so that the player can't spam shoot
                // Check if shooting is available
                if (model->coolDownCounter->get_value() == 0) {
                        // Let the player shoot
                        entity::Position position = model->player->position;
                        position.x += model->player->size.width/2.F;
                        shoot(position,entity::bulletType::laser,true);

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
                        break;
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

        // Do something in an extra loop


        // Move all the MoveObjects
        for (auto ptr : model->level.listOfCollideObjects) {

                if (ptr->getEntityType() == entity::entityType::enemy) {
                        auto castPtr = std::dynamic_pointer_cast<si::entity::Enemy>(ptr);
                        castPtr->move();

                        if (updateCycles >= cyclesPerSecond) {
                                castPtr->set_state(!castPtr->is_state());
                        }

                }else if (ptr->getEntityType() == entity::entityType::bullet){
                        auto castPtr = std::dynamic_pointer_cast<si::entity::Bullet>(ptr);
                        castPtr->move();

                }
        }

        if (updateCycles >= cyclesPerSecond) {
                updateCycles = 0;
        }

        // TODO: Spawn bullets randomly for the aliens

        // TODO: Check if any bullet collided with an object
        /*
        for( int i=0; i < model->level.listOfBullets.size(); ++i){
                auto bullet = model->level.listOfBullets.front();
                model->level.listOfBullets.pop_front();
                for(auto obj: model->level.listOfCollideObjects){
                        entity::checkCollision(bullet,obj);
                }
                if (!bullet->is_destroyed()){
                        model->level.listOfBullets.push_back(bullet);
                }
        }
         */

        // TODO check if an alien collided with the player or the ground
        for( int i=0; i < model->level.listOfCollideObjects.size(); ++i){
                auto entity = model->level.listOfCollideObjects.front();
                model->level.listOfCollideObjects.pop_front();
                for(auto obj: model->level.listOfCollideObjects){
                        entity::checkCollision(entity,obj);
                }
                if (!entity->is_destroyed()){
                        model->level.listOfCollideObjects.push_back(entity);
                }
        }

        // TODO Check if the ground was it best to check if alien has a y-cord < y

        // TODO Check if player got hit if yes repsawn with 1 life less handle death


        for (int i=0; i < model->level.listOfCollideObjects.size(); ++i){
                auto front = model->level.listOfCollideObjects.front();
                model->level.listOfCollideObjects.pop_front();
                if (!front->is_destroyed()){
                        model->level.listOfCollideObjects.push_back(front);
                }
        }



        for (int i=0; i < model->level.listOfEntities.size(); ++i){
                auto entity = model->level.listOfEntities.front();
                model->level.listOfEntities.pop_front();

                // Check that it is a collide object
                if (entity->getEntityType() != entity::entityType::counter){
                        if (!std::dynamic_pointer_cast<entity::CollideObject>(entity)->is_destroyed()){
                                model->level.listOfEntities.push_back(entity);
                        }
                }else{
                        model->level.listOfEntities.push_back(entity);
                }
        }



        // Increment the cycleCount
        ++updateCycles;
}
void si::mvc::Controller::shoot(si::entity::Position origin, si::entity::bulletType bullet_type, bool fromPlayer) const
{
        // Make the bullet
        int health = 1;
        unsigned int attack = 1;
        entity::Size size{0.06,0.12};
        entity::collideObjectType collide_object_type;
        entity::Position position{origin.x-size.width/2.f,origin.y - (size.height*!fromPlayer)};

        entity::MovePattern move_pattern{"P",0.125,15};

        if (fromPlayer){
                collide_object_type = entity::collideObjectType::friendly;
                move_pattern.pattern = "U";
        }else{
                collide_object_type = entity::collideObjectType::hostile;
                move_pattern.pattern = "D";
        }

        std::shared_ptr<entity::Bullet> bulletPrt = std::make_shared<entity::Bullet>(entity::Bullet{size,position,attack,collide_object_type,health,move_pattern,bullet_type});
        model->level.listOfCollideObjects.push_back(bulletPrt);
        model->level.listOfEntities.push_back(bulletPrt);
        model->level.listOfBullets.push_back(bulletPrt);
}
