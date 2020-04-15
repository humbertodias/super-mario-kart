#pragma once

#include <cmath>
#include <iostream>
#include <string>

#include "ai/gradientdescent.h"
#include "entities/collisionhashmap.h"
#include "entities/driver.h"
#include "entities/item.h"
#include "entities/lakitu.h"
#include "gui/gui.h"
#include "map/enums.h"
#include "map/map.h"
#include "states/statebase.h"

class StateRace : public State {
   private:
    const DriverPtr player;
    DriverArray drivers;
    RaceRankingArray& positions;

   public:
    static sf::Time currentTime;

    StateRace(Game& game, const DriverPtr& _player,
              const DriverArray& _drivers, RaceRankingArray& _positions)
        : State(game),
          player(_player),
          drivers(_drivers),
          positions(_positions) {
        init();
    }

    void usePowerUps(bool front, DriverPtr p);

    void handleEvent(const sf::Event& event) override;
    void fixedUpdate(const sf::Time& deltaTime) override;
    void draw(sf::RenderTarget& window) override;

    void init();
};