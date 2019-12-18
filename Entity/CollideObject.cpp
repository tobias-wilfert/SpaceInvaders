//============================================================================
// Name        : CollideObject.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "CollideObject.h"
#include <stdexcept>

si::entity::CollideObject::CollideObject(const si::entity::Size& size, const si::entity::Position& position,
                                         unsigned int attack_points, si::entity::collideObjectType type)
    : Entity(size, position), attackPoints(attack_points), type(type)
{
}

si::entity::collideObjectType si::entity::CollideObject::get_type() const { return type; }

bool si::entity::CollideObject::is_destroyed() const { return destroyed; }

void si::entity::CollideObject::set_destroyed(bool destroyed) { CollideObject::destroyed = destroyed; }

unsigned int si::entity::CollideObject::get_attack_points() const { return attackPoints; }

si::entity::Rectangle si::entity::CollideObject::getBound() const
{
        float topLeftX = position.x;
        float topLeftY = position.y;
        float bottomRightX = topLeftX + size.width;
        float bottomRightY = topLeftY - size.height;
        return si::entity::Rectangle{si::entity::Position(topLeftX, topLeftY),
                                     si::entity::Position(bottomRightX, bottomRightY)};
}

bool si::entity::collided(const si::entity::CollideObject& co1, const si::entity::CollideObject& co2)
{
        Position l1 = co1.getBound().topLeft;
        Position l2 = co2.getBound().topLeft;
        Position r1 = co1.getBound().bottomRight;
        Position r2 = co2.getBound().bottomRight;

        if (l1.x > r2.x || l2.x > r1.x) { // If one rectangle is on left side of other
                return false;
        } else if (l1.y < r2.y || l2.y < r1.y) { // If one rectangle is above other
                return false;
        } else {
                return true;
        }
}
void si::entity::checkCollision(std::shared_ptr<CollideObject> co1, std::shared_ptr<CollideObject> co2)
{
        // TODO: Check different type
        if (co1->get_type() == co2->get_type()){
                return;
        }



        // Check that both objects are not jet destroyed
        if (co1->is_destroyed() or co2->is_destroyed()) {
                return;
        }

        if (co1->isDead() or co2->isDead()) {
                throw std::logic_error("Object should not be dead and not yet destroyed");
        }

        // Check if they collide
        if (collided(*co1, *co2)) {
                // They collided
                co1->collide(co2->get_attack_points());
                co2->collide(co1->get_attack_points());
                // Set them destroyed if they are dead now
                co1->set_destroyed(co1->isDead());
                co2->set_destroyed(co2->isDead());
        } else {
                return;
        }
}
