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

float Transformation::convertXCoordinate(float xCoordinate) const
{
        if (xCoordinate < -3 or 3 < xCoordinate){
                throw std::invalid_argument("xCoordinate needs to be in [-3,3]");
        }
        return (xCoordinate+3.f)/6.f*static_cast<float>(windowWidth);
}

float Transformation::convertYCoordinate(float yCoordinate) const
{
        if (yCoordinate < -4 or 4 < yCoordinate){
                throw std::invalid_argument("yCoordinate needs to be in [-4,4]");
        }
        return (yCoordinate+4.f)/8.f*static_cast<float>(windowHeight);
}

float Transformation::convertWidth(float width) const { return width/6.f* static_cast<float>(windowWidth); }

float Transformation::convertHeight(float height) const { return height/8.f*static_cast<float>(windowHeight); }
