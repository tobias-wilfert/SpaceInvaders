//============================================================================
// Name        : Model.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_MODEL_H
#define SPACEINVADERS_MODEL_H

#include <memory>

#include "../Entity/Bullet.h"
#include "../Entity/Counter.h"
#include "../Entity/Enemy.h"
#include "../Entity/Immortal.h"
#include "../Entity/Player.h"
#include "../Entity/Shield.h"
#include "Level.h"

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
         \n Checks weather the player already interacted with the model thru the controller
         \n @return True if the player already interacted else false
         */
        bool is_interacted() const;

        /**
         \n Sets the level the model is currently operating on
         \n Adds all the level independent items to the level so that the View only needs to look at one place
         \n @param level The level the model should operate on
         */
        void set_level(const Level& level);

        /**
         * Returns true if the game is over else false
         * @return gameOver
         */
        bool is_game_over() const;

private:
        /// Make View friend of Model
        friend class View;
        /// Make Controller friend of Model
        friend class Controller;

        /// Used to lock the player in Title Screen till action is taken
        bool interacted{false};

        /// The movement speed of the player in int/seconds
        int playerMovementSpeed{3};

        // --- Entities that are level independent ---
        /**
         \n Pointer to the Player
         \n Fast and easy access for Controller
         \n Pointer so that it can all so be in the list of entities that can be hit
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
         \n The level the Model is currently at
         \n Contains all the bullets, aliens and shields
         \n Also all non level depend entities so that view only needs to look at one place
         */
        Level level;

        /// Indicates if the game should be ended
        bool gameOver{false};
};

} // namespace mvc
} // namespace si

#endif // SPACEINVADERS_MODEL_H
