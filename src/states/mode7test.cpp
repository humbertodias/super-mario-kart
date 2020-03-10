#include "mode7test.h"

void StateMode7Test::init() {
    posX = 0.0f;
    posY = 0.0f;
    posAngle = 0.0f;
    fovHalf = 0.4f;
    clipNear = 0.0005f;
    clipFar = 0.045f;

    speedForward = 0.0f;
    speedTurn = 0.0f;

    assetImageBottom.loadFromFile("assets/mario_circuit_2.png");
    assetImageTop.loadFromFile("assets/sky.jpeg");
}

void StateMode7Test::handleEvent(const sf::Event& event) {
    if (Input::pressed(Key::ITEM_FRONT, event)) {
        // TODO this is example code
        // we can handle item usage by creating an item entity
        // and removing the player's held item
    }
}

void StateMode7Test::fixedUpdate(const sf::Time& deltaTime) {
    // Friction
    speedForward = std::fmaxf(speedForward - 0.005f, 0.0f);
    speedTurn /= 1.2f;
    // Speed control
    if (Input::held(Key::ACCELERATE)) {
        speedForward = std::fminf(speedForward + 0.008f, 0.1f);
    }
    if (Input::held(Key::TURN_LEFT)) {
        speedTurn = std::fmaxf(speedTurn - 0.2f, -1.0f);
    }
    if (Input::held(Key::TURN_RIGHT)) {
        speedTurn = std::fminf(speedTurn + 0.2f, 1.0f);
    }
    // Speed & rotation changes
    posAngle += speedTurn * deltaTime.asSeconds();
    posX += cosf(posAngle) * speedForward * deltaTime.asSeconds();
    posY += sinf(posAngle) * speedForward * deltaTime.asSeconds();
}

void StateMode7Test::draw(sf::RenderTarget& window) {
    float farX1 = posX + cosf(posAngle - fovHalf) * clipFar;
    float farY1 = posY + sinf(posAngle - fovHalf) * clipFar;
    float nearX1 = posX + cosf(posAngle - fovHalf) * clipNear;
    float nearY1 = posY + sinf(posAngle - fovHalf) * clipNear;

    float farX2 = posX + cosf(posAngle + fovHalf) * clipFar;
    float farY2 = posY + sinf(posAngle + fovHalf) * clipFar;
    float nearX2 = posX + cosf(posAngle + fovHalf) * clipNear;
    float nearY2 = posY + sinf(posAngle + fovHalf) * clipNear;

    float width = game.getWindow().getSize().x;
    float halfHeight = game.getWindow().getSize().y / 2.0f;
    sf::Image bottomImage, topImage;
    bottomImage.create(width, halfHeight);
    topImage.create(width, halfHeight);
    for (int y = 1; y < halfHeight; y++) {
        float sampleDepth = y / halfHeight;

        float startX = (farX1 - nearX1) / sampleDepth + nearX1;
        float startY = (farY1 - nearY1) / sampleDepth + nearY1;
        float endX = (farX2 - nearX2) / sampleDepth + nearX2;
        float endY = (farY2 - nearY2) / sampleDepth + nearY2;

        for (int x = 0; x < width; x++) {
            float sampleWidth = x / width;
            float sampleX = (endX - startX) * sampleWidth + startX;
            float sampleY = (endY - startY) * sampleWidth + startY;

            sf::Color sampleBottom = sf::Color::Black;
            sf::Color sampleTop = sf::Color::Black;

            if (!(sampleX < 0 || sampleX > 1.0f || sampleY < 0 ||
                  sampleY > 1.0f)) {
                sampleX = fmodf(sampleX, 1.0f) * assetImageBottom.getSize().x;
                sampleY = fmodf(sampleY, 1.0f) * assetImageBottom.getSize().y;

                sampleBottom = assetImageBottom.getPixel(sampleX, sampleY);
                sampleTop = assetImageTop.getPixel(sampleX, sampleY);
            }
            bottomImage.setPixel(x, y, sampleBottom);
            topImage.setPixel(x, halfHeight - y, sampleTop);
        }
    }

    sf::Texture bottomTexture, topTexture;
    bottomTexture.loadFromImage(bottomImage);
    topTexture.loadFromImage(topImage);
    sf::Sprite bottomSprite(bottomTexture), topSprite(topTexture);
    bottomSprite.setPosition(sf::Vector2f(0.0f, halfHeight));
    window.draw(bottomSprite);
    window.draw(topSprite);
}