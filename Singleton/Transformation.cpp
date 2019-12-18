//============================================================================
// Name        : Transformation.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "Transformation.h"

std::shared_ptr<si::singleton::Transformation> si::singleton::Transformation::initialize(int width, int height)
{
        // Check that width and height are positive numbers
        if (width <= 0) {
                throw std::invalid_argument("Width needs to be strictly positive value");
        }
        if (height <= 0) {
                throw std::invalid_argument("Height needs to be strictly positive value");
        }

        if (!instance) { // The first time initialize() is called
                instance = std::make_shared<Transformation>(Transformation{width, height});
        } else {
                instance->set_width(width);
                instance->set_height(height);
        }
        return instance;
}

std::shared_ptr<si::singleton::Transformation> si::singleton::Transformation::getInstance()
{
        if (!instance) {
                throw std::invalid_argument("instance is nullptr. Transformation needs to be initialized first");
        }
        return instance;
}

int si::singleton::Transformation::get_width() const { return windowWidth; }

void si::singleton::Transformation::set_width(int width)
{
        if (width <= 0) {
                throw std::invalid_argument("Width needs to be strictly positive value");
        }
        Transformation::windowWidth = width;
}

int si::singleton::Transformation::get_height() const { return windowHeight; }

void si::singleton::Transformation::set_height(int height)
{
        if (height <= 0) {
                throw std::invalid_argument("Height needs to be strictly positive value");
        }
        Transformation::windowHeight = height;
}

si::singleton::Transformation::Transformation(int window_width, int window_height)
    : windowWidth(window_width), windowHeight(window_height)
{
}

float si::singleton::Transformation::convertXCoordinate(float xCoordinate) const
{
        return (xCoordinate + 3.f) / 6.f * static_cast<float>(windowWidth);
}

float si::singleton::Transformation::convertYCoordinate(float yCoordinate) const
{
        return (4.f - yCoordinate ) / 8.f * static_cast<float>(windowHeight);
}

float si::singleton::Transformation::convertWidth(float width) const
{
        return width / 6.f * static_cast<float>(windowWidth);
}

float si::singleton::Transformation::convertHeight(float height) const
{
        return height / 8.f * static_cast<float>(windowHeight);
}
