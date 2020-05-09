#pragma once

#define _USE_MATH_DEFINES
#include <array>
#include <cmath>

class StateRaceManager;

enum class RaceMode : int {
    GRAND_PRIX_1,  // can expand grand prixes here :-)
    VERSUS,
};

enum class RaceCircuit : int {
    DONUT_PLAINS_1,
    MARIO_CIRCUIT_2,
    GHOST_VALLEY_1,
    BOWSER_CASTLE_1,
    RAINBOW_ROAD,
    __COUNT,
};

const std::array<std::string, 5> CIRCUIT_DISPLAY_NAMES = {
    "donut plains 1",  "mario circuit 2", "ghost valley 1",
    "bowser castle 1", "rainbow road",
};

const std::array<std::string, 5> CIRCUIT_ASSET_NAMES = {
    "assets/circuit/donut_plains_1", "assets/circuit/mario_circuit_2",
    "assets/circuit/ghost_valley_1", "assets/circuit/bowser_castle_1",
    "assets/circuit/rainbow_road",
};

#include "entities/driver.h"
#include "entities/vehicleproperties.h"
#include "states/congratulations.h"
#include "states/gpstandings.h"
#include "states/playerselection.h"
#include "states/race.h"
#include "states/raceend.h"
#include "states/racestart.h"
#include "states/statebase.h"

class StateRaceManager : public State {
   private:
    RaceMode mode;
    RaceCircuit currentCircuit;
    DriverArray drivers;  // order should be the same as MenuPlayer
                          // not modified by other states

    MenuPlayer selectedPlayer;   // playerselection state modifies this
    RaceRankingArray positions;  // other states modify this to update positions
                                 // in the current race
                                 // index i -> position i+1 in race
                                 // e.g. first element is position 1 aka first
    GrandPrixRankingArray grandPrixRanking;  // driver-ints pairs

    enum class RaceState : int {
        NO_PLAYER,
        YES_PLAYER,
        RACING,
        STANDINGS,
        DONE,
    };

    RaceState currentState;

    void updatePositions();
    void setPlayer();

   public:
    StateRaceManager(Game &game, const RaceMode _mode,
                     const float _speedMultiplier,
                     const float _playerCharacterMultiplier,
                     const RaceCircuit _circuit = RaceCircuit(0))
        : State(game), mode(_mode) {
        init(_speedMultiplier, _playerCharacterMultiplier, _circuit);
    }
    void init(const float _speedMultiplier,
              const float _playerCharacterMultiplier,
              const RaceCircuit _circuit);
    void update(const sf::Time &deltaTime) override;

    inline std::string string() const override { return "RaceManager"; }
};