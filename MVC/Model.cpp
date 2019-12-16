//============================================================================
// Name        : Model.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Model.h"
si::mvc::Model::Model()
{
        entity::Size size{0.52,0.32};
        entity::Position position{-0.26,3.5};
        pplayer = std::shared_ptr<si::entity::Player>(new entity::Player{size,position,1,entity::collideObjectType::friendly,1});

}
bool si::mvc::Model::is_interacted() const { return interacted; }
