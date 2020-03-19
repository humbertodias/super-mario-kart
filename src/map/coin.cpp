#include "coin.h"

sf::Image Coin::assetsActive[];
sf::Image Coin::assetInactive;

void Coin::loadAssets(const std::string &assetName, sf::IntRect roi) {
    sf::Image rawImage;
    rawImage.loadFromFile(assetName);
    for (int i = 0; i < (int)Orientation::__COUNT; i++) {
        assetsActive[i].create(roi.width, roi.height);
        assetsActive[i].copy(rawImage, 0, 0, roi);
        roi.left += roi.width;
    }
    assetInactive.create(roi.width, roi.height);
    assetInactive.copy(rawImage, 0, 0, roi);
}

Coin::Coin(const sf::Vector2f &topLeftPixels, const Orientation _orientation)
    : FloorObject(topLeftPixels,
                  sf::Vector2f(assetsActive[(int)_orientation].getSize()),
                  Map::ASSETS_WIDTH, Map::ASSETS_HEIGHT, _orientation) {}

const sf::Image &Coin::getCurrentImage() const {
    return active ? assetsActive[(int)orientation] : assetInactive;
}

void Coin::interactWith(const DriverPtr &driver) {
    if (active) {
        active = false;
        // TODO
        // driver->coin();
        // gui::coinanimation();
    }
}