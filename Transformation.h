//============================================================================
// Name        : Transformation.h
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#ifndef SPACEINVADERS_TRANSFORMATION_H
#define SPACEINVADERS_TRANSFORMATION_H

#include <memory>

// TODO ask teacher about dimension specification

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
         \n Converts widthCoordinate to 2D game pixel
         \n @param widthCoordinate coordinate in [-3,3]
         \n @return coordinate in [0,windowWidth]
         */
        int convertWidthCoordinate(float widthCoordinate) const;

        /**
         \n Converts heightCoordinate to 2D game pixel
         \n @param heightCoordinate coordinate in [-4,4]
         \n @return coordinate in [0,windowHeight]
         */
        int convertHeightCoordinate(float heightCoordinate) const;

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
