#pragma once

#include <memory>
class State;
typedef std::shared_ptr<State> StatePtr;

#include <SFML/Graphics.hpp>
#include "game.h"

class State {
   protected:
    Game& game;

   public:
    State(Game& _game) : game(_game) {}
    // https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Event.php
    virtual void handleEvent(const sf::Event&) {}
    // update executes once per frame
    virtual void update(const sf::Time&) {}
    // fixedUpdate executes every fixed time step (physics calculations)
    virtual void fixedUpdate(const sf::Time&) {}
    virtual void draw(sf::RenderTarget&) {}
};