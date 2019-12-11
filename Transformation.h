//============================================================================
// Name        : Transformation.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_TRANSFORMATION_H
#define SPACEINVADERS_TRANSFORMATION_H

#include <memory>

// TODO: Ask teacher about dimension specification

/**
 \n Inspiration: https://www.tutorialspoint.com/Explain-Cplusplus-Singleton-design-pattern
 \n A Singleton implementation of a Transformation from [-4,4]x[-3,3] to 2D game pixels
 \n Invariant: windowWidth and windowHeight > 0
 \n Usage:
 \n std::shared_ptr<Transformation> Transformation::instance = nullptr;
 \n As Non-const static member must be initialized out of line
 \n std::shared_ptr<Transformation> t = Transformation::initialize(width,height);
 \n After that this is possible
 \n std::shared_ptr<Transformation> t2 = Transformation::getInstance();
 */
class Transformation
{
public:
        /**
         \n Act as De Facto constructor
         \n @pre width and height must be bigger than 0
         \n @throws invalid_argument("Width/Height needs to be strictly positive value");
         \n @param width The width of the Application Window
         \n @param height The height of the Application Window
         \n @return static std::shared_ptr<Transformation> instance
         */
        static std::shared_ptr<Transformation> initialize(int width, int  height);

        /**
         \n @pre Checks if instance is not nullptr
         \n @throws invalid_argument("instance is nullptr. Transformation needs to be initialized first");
         \n @return static std::shared_ptr<Transformation> instance
         */
        static std::shared_ptr<Transformation> getInstance();

        // Get the width
        int get_width() const;

        /**
         \n @pre width must be bigger than 0
         \n @throws invalid_argument("Width needs to be strictly positive value");
         */
        void set_width(int width);

        // Get the height
        int get_height() const;

        /**
         \n @pre height must be bigger than 0
         \n @throws invalid_argument("Height needs to be strictly positive value");
         */
        void set_height(int height);

        /**
         \n Converts xCoordinate to 2D game pixel
         \n @param xCoordinate coordinate in [-3,3]
         \n @return coordinate in [0,windowWidth]
         */
        float convertXCoordinate(float xCoordinate) const;

        /**
         \n Converts yCoordinate to 2D game pixel
         \n @param yCoordinate coordinate in [-4,4]
         \n @return coordinate in [0,windowHeight]
         */
        float convertYCoordinate(float yCoordinate) const;

        /**
         * Scales the width to 2D game pixel
         * @param width size relative to [-3,3]
         * @return width scaled relative to [0,windowWidth]
         */
        float convertWidth(float width) const;

        /**
         * Scales the height to 2D game pixel
         * @param height size relative to [-4,4]
         * @return height scaled relative to [0,windowHeight]
         */
        float convertHeight(float height) const;

private:

        //The width of the Application Window
        int windowWidth;

        //The height of the Application Window
        int windowHeight;

        // Smart pointer to an instance of Transformation that is shared by all instances of Transformation
        static std::shared_ptr<Transformation> instance;

        /**
         * Private constructor causing only 1 instance ot Transformation to be allowed
         * @param window_width The width of the Application Window
         * @param window_height The height of the Application Window
         */
        Transformation(int window_width, int window_height);
};

#endif // SPACEINVADERS_TRANSFORMATION_H
