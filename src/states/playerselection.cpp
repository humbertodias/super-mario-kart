#include "playerselection.h"

sf::Texture StatePlayerSelection::assetBackground,
    StatePlayerSelection::assetPlayerBackground,
    StatePlayerSelection::assetMarquee;
sf::Texture StatePlayerSelection::asset1P, StatePlayerSelection::asset1POkQ,
    StatePlayerSelection::asset1POk;

const std::array<sf::Vector2f, (int)StatePlayerSelection::MenuPlayer::__COUNT>
    StatePlayerSelection::PLAYER_CELL_ORIGINS = {
        sf::Vector2f(37.0f / BACKGROUND_WIDTH, 64.0f / BACKGROUND_HEIGHT),
        sf::Vector2f(85.0f / BACKGROUND_WIDTH, 64.0f / BACKGROUND_HEIGHT),
        sf::Vector2f(133.0f / BACKGROUND_WIDTH, 64.0f / BACKGROUND_HEIGHT),
        sf::Vector2f(181.0f / BACKGROUND_WIDTH, 64.0f / BACKGROUND_HEIGHT),
        sf::Vector2f(37.0f / BACKGROUND_WIDTH, 128.0f / BACKGROUND_HEIGHT),
        sf::Vector2f(85.0f / BACKGROUND_WIDTH, 128.0f / BACKGROUND_HEIGHT),
        sf::Vector2f(133.0f / BACKGROUND_WIDTH, 128.0f / BACKGROUND_HEIGHT),
        sf::Vector2f(181.0f / BACKGROUND_WIDTH, 128.0f / BACKGROUND_HEIGHT),
};
const sf::Vector2f StatePlayerSelection::REL_TICK =
    sf::Vector2f(11.0f / BACKGROUND_WIDTH, 0.0f / BACKGROUND_HEIGHT);
const sf::Vector2f StatePlayerSelection::REL_BACKGROUND =
    sf::Vector2f(0.0f / BACKGROUND_WIDTH, 14.0f / BACKGROUND_HEIGHT);
const sf::Vector2f StatePlayerSelection::REL_PLAYER =
    sf::Vector2f(19.0f / BACKGROUND_WIDTH, 49.0f / BACKGROUND_HEIGHT);
const sf::Vector2f StatePlayerSelection::ABS_MARQUEE =
    sf::Vector2f(80.0f / BACKGROUND_WIDTH, 24.0f / BACKGROUND_HEIGHT);
const sf::Vector2f StatePlayerSelection::ABS_CONFIRM =
    sf::Vector2f(191.0f / BACKGROUND_WIDTH, 191.0f / BACKGROUND_HEIGHT);

const sf::Time StatePlayerSelection::FADE_TOTAL_TIME = sf::seconds(2.0f);

void StatePlayerSelection::loadAssets(const std::string &assetName,
                                      const sf::IntRect &roiBackground,
                                      const sf::IntRect &roiPlayerBackground,
                                      const sf::IntRect &roiMarquee,
                                      const sf::IntRect &roi1P,
                                      const sf::IntRect &roi1POkQ,
                                      const sf::IntRect &roi1POk) {
    assetBackground.loadFromFile(assetName, roiBackground);
    assetPlayerBackground.loadFromFile(assetName, roiPlayerBackground);
    assetMarquee.loadFromFile(assetName, roiMarquee);
    asset1P.loadFromFile(assetName, roi1P);
    asset1POkQ.loadFromFile(assetName, roi1POkQ);
    asset1POk.loadFromFile(assetName, roi1POk);
}

void StatePlayerSelection::init() {
    currentState = SelectionState::NO_SELECTION;
    selectedPlayer = (MenuPlayer)0;  // select first player
    framesSinceOrigin = 0;

    animators.clear();
    for (int i = 0; i < (int)MenuPlayer::__COUNT; i++) {
        std::string filename;
        switch (MenuPlayer(i)) {
            case MenuPlayer::MARIO:
                filename = "mario.png";
                break;
            case MenuPlayer::PEACH:
                filename = "peach.png";
                break;
            case MenuPlayer::BOWSER:
                filename = "bowser.png";
                break;
            case MenuPlayer::KOOPA:
                filename = "koopa.png";
                break;
            case MenuPlayer::LUIGI:
                filename = "luigi.png";
                break;
            case MenuPlayer::YOSHI:
                filename = "yoshi.png";
                break;
            case MenuPlayer::DK:
                filename = "dk.png";
                break;
            case MenuPlayer::TOAD:
                filename = "toad.png";
                break;
            default:
                break;
        }
        std::string full = "assets/drivers/" + filename;
        animators.push_back(DriverAnimator(full.c_str()));
        angles[i] = 0.3f;
    }
}

void StatePlayerSelection::handleEvent(const sf::Event &event) {
    static constexpr const int count = (int)MenuPlayer::__COUNT;
    static constexpr const int halfCount = count / 2;

    switch (currentState) {
        case SelectionState::NO_SELECTION: {
            // cursor movement
            int selectedPlayerId = (int)selectedPlayer;
            if (Input::pressed(Key::MENU_LEFT, event)) {
                selectedPlayerId = (selectedPlayerId - 1) % count;
            } else if (Input::pressed(Key::MENU_RIGHT, event)) {
                selectedPlayerId = (selectedPlayerId + 1) % count;
            } else if (Input::pressed(Key::MENU_UP, event)) {
                selectedPlayerId = (selectedPlayerId - halfCount) % count;
            } else if (Input::pressed(Key::MENU_DOWN, event)) {
                selectedPlayerId = (selectedPlayerId + halfCount) % count;
            } else if (Input::pressed(Key::ACCEPT, event)) {
                // confirmation
                currentState = SelectionState::AWAIT_CONFIRMATION;
            }
            if (selectedPlayerId < 0) selectedPlayerId += count;
            selectedPlayer = (MenuPlayer)selectedPlayerId;
        } break;
        case SelectionState::AWAIT_CONFIRMATION:
            if (Input::pressed(Key::ACCEPT, event)) {
                currentState = SelectionState::SELECTED;
                // TODO player selected callback
                fadeCurrentTime = sf::Time::Zero;
            } else if (Input::pressed(Key::CANCEL, event)) {
                currentState = SelectionState::NO_SELECTION;
            }
            break;
        default:
            break;
    }
}

void StatePlayerSelection::fixedUpdate(const sf::Time &deltaTime) {
    framesSinceOrigin++;
    if (currentState == SelectionState::SELECTED) {
        fadeCurrentTime += deltaTime;
        if (fadeCurrentTime > FADE_TOTAL_TIME) {
            game.popState();
        }
    }

    for (int i = 0; i < (int)MenuPlayer::__COUNT; i++) {
        float &angle = angles[i];
        if (currentState != SelectionState::NO_SELECTION &&
            (int)selectedPlayer == i) {
            angle = std::fminf(angle + 2.5f * deltaTime.asSeconds(), M_PI_2);
        } else {
            angle = std::fmaxf(angle - 4.5f * deltaTime.asSeconds(), 0.3f);
        }
    }
}

void StatePlayerSelection::draw(sf::RenderTarget &window) {
    sf::Vector2u windowSize = window.getSize();
    float scale = windowSize.x / assetBackground.getSize().x;
    for (uint i = 0; i < (int)MenuPlayer::__COUNT; i++) {
        sf::Vector2f origin = PLAYER_CELL_ORIGINS[i];
        sf::Vector2f backgroundPos = origin + REL_BACKGROUND;
        sf::Vector2f playerPos = origin + REL_PLAYER;
        sf::Sprite background(assetPlayerBackground);
        background.setScale(scale, scale);
        background.setPosition(backgroundPos.x * windowSize.x,
                               backgroundPos.y * windowSize.y);
        sf::Sprite player;
        player = animators[i].getMinimapSprite(angles[i]);
        player.setScale(scale, scale);
        player.setPosition(playerPos.x * windowSize.x,
                           playerPos.y * windowSize.y);
        // move players one pixel up and down (depends on fps)
        if ((framesSinceOrigin / 10) % 3 == (5 * i) % 3 &&
            i != (uint)selectedPlayer) {
            player.move(0.0f, -1.0f);
        }
        window.draw(background);
        window.draw(player);
    }
    // marquees brownlee
    sf::Sprite marquee(assetMarquee);
    marquee.setScale(scale, scale);
    marquee.setPosition(ABS_MARQUEE.x * windowSize.x,
                        ABS_MARQUEE.y * windowSize.y);
    float pixelsRight = framesSinceOrigin % assetMarquee.getSize().x;
    // move left, so change sign
    marquee.move((pixelsRight * -1.0f + MARQUEE_SPACE_WIDTH) * scale, 0.0f);
    window.draw(marquee);
    // background over all this
    sf::Sprite background(assetBackground);
    background.setScale(scale, scale);
    background.setPosition(0.0f, 0.0f);
    window.draw(background);
    // 1P tick sign blinks every X frames (framerate-dependent, but who cares)
    if (currentState != SelectionState::NO_SELECTION ||
        framesSinceOrigin % 7 != 0) {
        sf::Vector2f signPos =
            PLAYER_CELL_ORIGINS[(int)selectedPlayer] + REL_TICK;
        sf::Sprite tick(asset1P);
        tick.setScale(scale, scale);
        tick.setPosition(signPos.x * windowSize.x, signPos.y * windowSize.y);
        window.draw(tick);
    }

    // confirmation buttons below
    if (currentState != SelectionState::NO_SELECTION) {
        sf::Sprite button;
        if (currentState == SelectionState::AWAIT_CONFIRMATION) {
            button.setTexture(asset1POkQ);
        } else {
            button.setTexture(asset1POk);
        }
        button.setScale(scale, scale);
        button.setPosition(ABS_CONFIRM.x * windowSize.x,
                           ABS_CONFIRM.y * windowSize.y);
        window.draw(button);
    }

    // fade to black if necessary
    if (currentState == SelectionState::SELECTED) {
        float pct = fadeCurrentTime / FADE_TOTAL_TIME;
        int alpha = std::max(pct * 255.0f, 0.0f);
        sf::Image black;
        black.create(windowSize.x, windowSize.y, sf::Color::Black);
        sf::Texture blackTex;
        blackTex.loadFromImage(black);
        sf::Sprite blackSprite(blackTex);
        blackSprite.setPosition(0.0f, 0.0f);
        blackSprite.setColor(sf::Color(255, 255, 255, alpha));
        window.draw(blackSprite);
    }
}