//============================================================================
// Name        : Model.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_MODEL_H
#define SPACEINVADERS_MODEL_H

#include "../Entity/Counter.h"
#include "../Entity/Immortal.h"
#include "../Entity/Player.h"
#include "Level.h"

#include <memory>

/// Namespace of SpaceInvaders
namespace si {

/// Namespace of Model View Controller
namespace mvc {

/**
 * The Model of the MVC
 */
class Model
{
public:
        Model();

        /**
         * Checks weather the player already interacted with the model thru the controller
         * @return True if the player already interacted else false
         */
        bool is_interacted() const;

        void set_level(const Level& level);

private:
        /// Make View friend of Model
        friend class View;
        /// Make Controller friend of Model
        friend class Controller;

        /// Used to lock the player in Title Screen till action is taken
        bool interacted{false};

        // --- Entities that are level independent ---
        /**
         * Pointer to the Player
         * Fast and easy access for Controller
         * Pointer so that it can all so be in the list of entities that can be hit
         */
        std::shared_ptr<si::entity::Player> player;

        /// Top bound of the window
        std::shared_ptr<si::entity::Immortal> sky;

        /// Bottom bound of the window
        std::shared_ptr<si::entity::Immortal> earth;

        /// Score Counter
        std::shared_ptr<si::entity::Counter> scoreCounter;

        /// health Counter
        std::shared_ptr<si::entity::Counter> healthCounter;

        /// health Counter
        std::shared_ptr<si::entity::Counter> coolDownCounter;

        /**
         * The level the Model is currently at
         * Contains all the bullets, aliens and shields
         * Also all non level depend entities so that view only needs to look at one place
         */
        Level level;

        // Get all enties in one list for the view

        // - Update all the bullets movement

        // - Update all the alien movement -> could be specified in file as LLRR=(left,left,right,right)

        // All of the info the Model holds

        // Model should hold some items

        // While others should be held by the level
        // -> Player, Counter and immortal are independent of level
        //   L-> Maybe change position but that is all
        // -> Aliens, Bullets and Shields are level dependent

        // List of all entities for view to draw

        // Player, Counter and Immortal

        // List of all collide objects for the game logic
};

} // namespace mvc
} // namespace si

#endif // SPACEINVADERS_MODEL_H
