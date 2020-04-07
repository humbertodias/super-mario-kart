#pragma once

#include <SFML/Graphics.hpp>

enum class Key : int {
    // Driving actions
    ACCELERATE,
    BRAKE,
    TURN_LEFT,
    TURN_RIGHT,
    ITEM_FRONT,
    ITEM_BACK,
    // Menu actions
    PAUSE,
    CONTINUE,
    ACCEPT,
    CANCEL,
    MENU_UP,
    MENU_DOWN,
    MENU_LEFT,
    MENU_RIGHT,
    __COUNT
};

class Input {
   private:
    static Input instance;
    sf::Keyboard::Key map[(int)Key::__COUNT];

    Input();

   public:
    // Read/write the key map
    static inline void set(const Key action, const sf::Keyboard::Key code) {
        instance.map[(int)action] = code;
    }
    static inline const sf::Keyboard::Key &get(Key action) {
        return instance.map[(int)action];
    }

    // Check for key press/release/hold events
    static inline bool pressed(const Key action, const sf::Event &event) {
        return event.type == sf::Event::KeyPressed &&
               event.key.code == get(action);
    }
    static inline bool released(const Key action, const sf::Event &event) {
        return event.type == sf::Event::KeyReleased &&
               event.key.code == get(action);
    }
    static inline bool held(const Key action) {
        return sf::Keyboard::isKeyPressed(get(action));
    }

    // returns true if key is accepted in game
    static std::string getActionName(const Key action);

    // code based on:
    // https://en.sfml-dev.org/forums/index.php?topic=15226.0
    // returns true if key is accepted in game
    static std::string getKeyCodeName(const sf::Keyboard::Key code);
};