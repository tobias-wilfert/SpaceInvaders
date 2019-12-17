//============================================================================
// Name        : View.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "View.h"

si::mvc::View::View(std::shared_ptr<Model>  model,
    std::shared_ptr<singleton::Transformation>  transformation)
    : model(std::move(model)), transformation(std::move(transformation))
{
        // TODO Handel error and if needed Destruct View
        initializerResources();
}

void si::mvc::View::initializerResources()
{

        // Load the Font that will be used
        if (!font.loadFromFile("../resources/fonts/KenPixel.ttf")) {
                std::cout << "Error loading file" << std::endl;
                system("pause");
                // TODO Error Handling
        }

        // Load the Textures that will be used
        // PLayer
        playerTexture = loadFromFile("../resources/img/player.png");

        // Alien A
        alienA = std::make_tuple(loadFromFile("../resources/img/alien-a1.png"),
            loadFromFile("../resources/img/alien-a2.png"));

        // Alien B
        alienB = std::make_tuple(loadFromFile("../resources/img/alien-b1.png"),
            loadFromFile("../resources/img/alien-b2.png"));

        // Alien C
        alienC = std::make_tuple(loadFromFile("../resources/img/alien-c1.png"),
            loadFromFile("../resources/img/alien-c2.png"));

        // Alien M
        alienM = std::make_tuple(loadFromFile("../resources/img/mothership-a.png"),
            loadFromFile("../resources/img/mothership-b.png"));
}

sf::Texture si::mvc::View::loadFromFile(std::string path) const
{
        sf::Texture texture;

        if (!texture.loadFromFile(path)) {
                std::cout << "Load failed:" << path << std::endl;
                system("pause");
                // TODO Error Handling
        }

        return texture;
}

void si::mvc::View::display(sf::RenderWindow& window) const
{
        // Clear the window
        // This causes MVC to be not a clean as in Swift as we need to re draw everything even when it didn't change.
        window.clear();

        // Draw all the entities
        for (const auto& ptr : model->level.listOfEntities) {
                drawEntity(ptr, window);
        }

        // Display the new updated interface to the user
        window.display();
}


void si::mvc::View::drawEntity(const std::shared_ptr<si::entity::Entity>& entity, sf::RenderWindow& window) const
{
        // Switch over all possible types
        switch (entity->getEntityType()) {
        case entity::entityType::counter:
                drawCounter(entity, window);
                break;
        case entity::entityType::immortal:
                // Immortals don't have an appearance
                break;
        case entity::entityType::player:
                drawPlayer(entity,window);
                break;
        case entity::entityType::shield:

                break;
        case entity::entityType::enemy:

                break;
        case entity::entityType::bullet:

                break;
        default:
                break;
        }
}

void si::mvc::View::drawCounter(const std::shared_ptr<si::entity::Entity>& entity, sf::RenderWindow& window) const
{
        std::shared_ptr<si::entity::Counter> counter = std::dynamic_pointer_cast<si::entity::Counter>(entity);

        sf::Text title;
        title.setFont(font);
        title.setCharacterSize(30);
        title.setFillColor(sf::Color::Cyan);
        title.setPosition(transformation->convertXCoordinate(entity->position.x),
                          transformation->convertYCoordinate(entity->position.y));

        /* Debugging
        sf::RectangleShape rect = entityToRectangle(counter);
        rect.setFillColor(sf::Color::Black);
        window.draw(rect);
         */

        if (counter->get_counter_type() == si::entity::counterType::health) {
                title.setString(" Life:");

                // Draw the player icon to indicate life
                sf::RectangleShape lifeIndicator;
                lifeIndicator.setTexture(&playerTexture);
                lifeIndicator.setSize(
                    sf::Vector2f(transformation->convertWidth(0.35), transformation->convertHeight(0.22)));

                for (int i = 0; i < counter->get_value(); ++i) {

                        lifeIndicator.setPosition(transformation->convertXCoordinate(entity->position.x + 0.8 + 0.4*i),
                                                  transformation->convertYCoordinate(entity->position.y));
                        window.draw(lifeIndicator);
                }

        } else if (counter->get_counter_type() == si::entity::counterType::score) {
                // Size made to fit nicely with  100,000,000
                title.setString(" Score: "+ std::to_string(counter->get_value()));

        } else if (counter->get_counter_type() == si::entity::counterType::cooldown) {
                if (counter->get_value() == 0){
                        title.setString(" Gun ready");
                }else{
                        title.setString(" Gun ready in : "+ std::to_string(counter->get_value()/20+1));
                }

        }

        // Draw
        window.draw(title);
}

void si::mvc::View::drawPlayer(const std::shared_ptr<si::entity::Entity>& entity, sf::RenderWindow& window) const
{
        sf::RectangleShape player = entityToRectangle(entity);
        player.setTexture(&playerTexture);
        window.draw(player);
}

sf::RectangleShape si::mvc::View::entityToRectangle(const std::shared_ptr<si::entity::Entity>& entity) const
{
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(transformation->convertWidth(entity->size.width),
            transformation->convertHeight(entity->size.height)));

        rect.setPosition(transformation->convertXCoordinate(entity->position.x),
            transformation->convertYCoordinate(entity->position.y));

        return rect;
}

void si::mvc::View::displayTitleScreen(sf::RenderWindow& window) const
{
        // TODO: Add extra info the title screen
        sf::Text title("Space Invaders", font, 50);
        sf::Rect<float> size = title.getGlobalBounds();
        title.setPosition(window.getSize().x / 2.f - size.width / 2.f, window.getSize().y / 2.f - size.height / 2.f);

        window.clear();
        window.draw(title);
        window.display();
}

