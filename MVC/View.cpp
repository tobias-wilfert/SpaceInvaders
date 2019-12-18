//============================================================================
// Name        : View.cpp
// Author      : Tobias Wilfert
// Copyright   : Tobias Wilfert - University of Antwerp
//============================================================================

#include "View.h"

si::mvc::View::View(std::shared_ptr<Model> model, std::shared_ptr<singleton::Transformation> transformation)
    : model(std::move(model)), transformation(std::move(transformation))
{
        // TODO Handel error and if needed Destruct View
        initializerResources();
}

void si::mvc::View::initializerResources()
{

        try {
                // Load the Font that will be used
                if (!font.loadFromFile("../resources/fonts/KenPixel.ttf")) {
                        throw std::runtime_error("Failed to allocate resources at: ../resources/fonts/KenPixel.ttf");
                }

                // Load the Textures that will be used
                // PLayer
                playerTexture = loadFromFile("../resources/img/player.png");

                // Alien A
                alienA = std::array<sf::Texture, 2>{loadFromFile("../resources/img/alien-a1.png"),
                                                    loadFromFile("../resources/img/alien-a2.png")};

                // Alien B
                alienB = std::array<sf::Texture, 2>{loadFromFile("../resources/img/alien-b1.png"),
                                                    loadFromFile("../resources/img/alien-b2.png")};

                // Alien C
                alienC = std::array<sf::Texture, 2>{loadFromFile("../resources/img/alien-c1.png"),
                                                    loadFromFile("../resources/img/alien-c2.png")};

                // Alien M
                alienM = std::array<sf::Texture, 2>{loadFromFile("../resources/img/mothership-a.png"),
                                                    loadFromFile("../resources/img/mothership-b.png")};

                // Bullets
                bullets = std::array<sf::Texture, 3>{loadFromFile("../resources/img/laser.png"),
                                                     loadFromFile("../resources/img/bullet-up.png"),
                                                     loadFromFile("../resources/img/bullet-down.png")};

                // Shields
                shields = std::array<sf::Texture, 4>{loadFromFile("../resources/img/shield-100.png"),
                                                     loadFromFile("../resources/img/shield-75.png"),
                                                     loadFromFile("../resources/img/shield-50.png"),
                                                     loadFromFile("../resources/img/shield-25.png")};

        } catch (const std::exception& e) {
                std::cerr << "Failed to load resources need for SpaceInvders" << std::endl;
                std::cerr << e.what() << std::endl;
                exit(1);
        }
}

sf::Texture si::mvc::View::loadFromFile(std::string path) const
{
        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
                throw std::runtime_error("Failed to allocate resources at: "+path);
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
        // Switch over all possible types and delegate the draw
        switch (entity->getEntityType()) {
        case entity::entityType::counter:
                drawCounter(std::dynamic_pointer_cast<si::entity::Counter>(entity), window);
                break;
        case entity::entityType::immortal:
                // Immortals don't have an appearance
                break;
        case entity::entityType::player:
                drawPlayer(std::dynamic_pointer_cast<si::entity::Player>(entity), window);
                break;
        case entity::entityType::shield:
                drawShield(std::dynamic_pointer_cast<si::entity::Shield>(entity),window);
                break;
        case entity::entityType::enemy:
                drawEnemy(std::dynamic_pointer_cast<si::entity::Enemy>(entity), window);
                break;
        case entity::entityType::bullet:
                drawBullet(std::dynamic_pointer_cast<si::entity::Bullet>(entity), window);
                break;
        }
}

void si::mvc::View::drawCounter(const std::shared_ptr<si::entity::Counter>& counter, sf::RenderWindow& window) const
{
        // TODO: Adjust font to the Screen resolution
        sf::Text title;
        title.setFont(font);
        title.setCharacterSize(30);
        title.setFillColor(sf::Color::Cyan);
        title.setPosition(transformation->convertXCoordinate(counter->position.x),
                          transformation->convertYCoordinate(counter->position.y));

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

                        lifeIndicator.setPosition(
                            transformation->convertXCoordinate(counter->position.x + 0.8 + 0.4 * i),
                            transformation->convertYCoordinate(counter->position.y));
                        window.draw(lifeIndicator);
                }

        } else if (counter->get_counter_type() == si::entity::counterType::score) {
                // Size made to fit nicely with  100,000,000
                title.setString(" Score: " + std::to_string(counter->get_value()));

        } else if (counter->get_counter_type() == si::entity::counterType::cooldown) {
                if (counter->get_value() == 0) {
                        title.setString(" Gun ready");
                } else {
                        title.setString(" Gun ready in : " + std::to_string(counter->get_value() / 20 + 1));
                }
        }

        // Draw
        window.draw(title);
}

void si::mvc::View::drawPlayer(const std::shared_ptr<si::entity::Player>& player, sf::RenderWindow& window) const
{
        sf::RectangleShape playerRect = entityToRectangle(player);
        playerRect.setTexture(&playerTexture);
        window.draw(playerRect);
}

void si::mvc::View::drawEnemy(const std::shared_ptr<si::entity::Enemy>& enemy, sf::RenderWindow& window) const
{
        sf::RectangleShape enemyRect = entityToRectangle(enemy);


        switch (enemy->get_enemy_type()){
        case entity::enemyType::a :
                enemyRect.setTexture(&alienA[enemy->is_state()]);
                break;
        case entity::enemyType::b :
                enemyRect.setTexture(&alienB[enemy->is_state()]);
                break;
        case entity::enemyType::c :
                enemyRect.setTexture(&alienC[enemy->is_state()]);
                break;
        case entity::enemyType::m :
                enemyRect.setTexture(&alienM[enemy->is_state()]);
                break;
        }

        enemyRect.setFillColor(gameColourToSFMLColour(enemy->get_colour()));
        window.draw(enemyRect);
}

void si::mvc::View::drawShield(const std::shared_ptr<si::entity::Shield>& shield, sf::RenderWindow& window) const
{
        sf::RectangleShape shieldRect = entityToRectangle(shield);

        float relativeHealth =
            static_cast<float>(shield->get_health_points()) / static_cast<float>(shield->get_initial_health());

        if (relativeHealth > 0.75) {
                shieldRect.setTexture(&shields[0]);
        } else if (relativeHealth > 0.5) {
                shieldRect.setTexture(&shields[1]);
        } else if (relativeHealth > 0.25) {
                shieldRect.setTexture(&shields[2]);
        } else {
                shieldRect.setTexture(&shields[3]);
        }

        window.draw(shieldRect);
}

void si::mvc::View::drawBullet(const std::shared_ptr<si::entity::Bullet>& bullet, sf::RenderWindow& window) const
{
        sf::RectangleShape bulletRect = entityToRectangle(bullet);

        switch (bullet->get_bullet_type()){
        case entity::bulletType::laser :
                bulletRect.setTexture(&bullets[0]);
                break;
        case entity::bulletType::up :
                bulletRect.setTexture(&bullets[1]);
                break;
        case entity::bulletType::down :
                bulletRect.setTexture(&bullets[2]);
                break;
        }
        // TODO: Maybe add Color?

        window.draw(bulletRect);
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
sf::Color si::mvc::View::gameColourToSFMLColour(const si::entity::colourType colour) const
{
        sf::Color c;
        switch (colour) {
        case entity::colourType::white:
                c = sf::Color::White;
                break;
        case entity::colourType::red:
                c = sf::Color::Red;
                break;
        case entity::colourType::green:
                c = sf::Color::Green;
                break;
        case entity::colourType::blue:
                c = sf::Color::Blue;
                break;
        case entity::colourType::yellow:
                c = sf::Color::Yellow;
                break;
        case entity::colourType::magenta:
                c = sf::Color::Magenta;
                break;
        case entity::colourType::cyan:
                c = sf::Color::Cyan;
                break;
        }
        return c;
}
