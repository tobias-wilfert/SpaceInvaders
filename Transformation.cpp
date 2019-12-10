//============================================================================
// Name        : Transformation.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Transformation.h"

std::shared_ptr<Transformation> Transformation::initialize(int width, int height)
{
        // Check that width and height are positive numbers
        if (width <= 0){ throw std::invalid_argument("Width needs to be strictly positive value");}
        if (height <= 0){ throw std::invalid_argument("Height needs to be strictly positive value");}

        if (!instance) { // The first time initialize() is called
                instance = std::make_shared<Transformation>(Transformation{width,height});
        }else{
                instance->set_width(width);
                instance->set_height(height);
        }
        return instance;
}

std::shared_ptr<Transformation> Transformation::getInstance()
{
        if (!instance) { throw std::invalid_argument("instance is nullptr. Transformation needs to be initialized first");}
        return instance;
}

int Transformation::get_width() const { return windowWidth; }

void Transformation::set_width(int width)
{
        if (width <= 0){ throw std::invalid_argument("Width needs to be strictly positive value");}
        Transformation::windowWidth = width;
}

int Transformation::get_height() const { return windowHeight; }

void Transformation::set_height(int height)
{
        if (height <= 0){ throw std::invalid_argument("Height needs to be strictly positive value");}
        Transformation::windowHeight = height;
}

Transformation::Transformation(int window_width, int window_height)
    : windowWidth(window_width), windowHeight(window_height){}

int Transformation::convertWidthCoordinate(float widthCoordinate) const
{
        if (widthCoordinate < -3 or 3 < widthCoordinate){
                throw std::invalid_argument("widthCoordinate needs to be in [-3,3]");
        }
        return (widthCoordinate+3)/6*windowWidth;
}

int Transformation::convertHeightCoordinate(float heightCoordinate) const
{
        if (heightCoordinate < -4 or 4 < heightCoordinate){
                throw std::invalid_argument("heightCoordinate needs to be in [-4,4]");
        }
        return (heightCoordinate+4)/8*windowHeight;
}
