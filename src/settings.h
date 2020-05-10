#pragma once

class Settings;

#include <iostream>
#include <fstream>
#include "audio/audio.h"
#include "input/input.h"
#include <SFML/Graphics.hpp>

static const std::string FILE_NAME = "settings.txt";

static const std::string MUSIC_VOLUME = "MUSIC_VOLUME";
static const std::string SFX_VOLUME = "SFX_VOLUME";
static const std::string RESOLUTION_Y = "RESOLUTION_Y";
static const std::string RESOLUTION_X = "RESOLUTION_X";

class Settings {
   private:
    Settings();
    static Settings inst;

   public:
    static void loadSettings();
    static void saveSettings(sf::Vector2u resolution);

};