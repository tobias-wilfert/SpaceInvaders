//
// Created by Tobias Wilfert on 12/12/2019.
//

#include "CollideObject.h"

si::Rectangle si::CollideObject::getBound() const
{
        float topLeftX = position.x;
        float topLeftY = position.y;
        float bottomRightX = topLeftX + size.width;
        float bottomRightY = topLeftY + size.height;
        return si::Rectangle{si::Position(topLeftX,topLeftY),si::Position(bottomRightX,bottomRightY)};
}


bool si::collided(const si::CollideObject& co1, const si::CollideObject& co2)
{
        Position l1 = co1.getBound().topLeft;
        Position l2 = co2.getBound().topLeft;
        Position r1 = co1.getBound().bottomRight;
        Position r2 = co2.getBound().bottomRight;

        if (l1.x > r2.x || l2.x > r1.x){ // If one rectangle is on left side of other
                return false;
        }else if (l1.y < r2.y || l2.y < r1.y) { // If one rectangle is above other
                return false;
        }else{
                return true;
        }
}
