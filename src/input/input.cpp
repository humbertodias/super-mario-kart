#include "input.h"

Input Input::instance;

Input::Input() {
    // Driving actions
    set(Key::ACCELERATE, sf::Keyboard::Key::X);
    set(Key::BRAKE, sf::Keyboard::Key::Z);
    set(Key::DRIFT, sf::Keyboard::Key::C);
    set(Key::TURN_LEFT, sf::Keyboard::Key::Left);
    set(Key::TURN_RIGHT, sf::Keyboard::Key::Right);
    set(Key::ITEM_FRONT, sf::Keyboard::Key::Up);
    set(Key::ITEM_BACK, sf::Keyboard::Key::Down);
    // Menu actions
    set(Key::PAUSE, sf::Keyboard::Key::Escape);
    // set(Key::CONTINUE, sf::Keyboard::Key::Enter);  // [[ deprecated ]]
    set(Key::ACCEPT, sf::Keyboard::Key::Enter);
    set(Key::CANCEL, sf::Keyboard::Key::Escape);
    set(Key::MENU_UP, sf::Keyboard::Key::Up);
    set(Key::MENU_DOWN, sf::Keyboard::Key::Down);
    set(Key::MENU_LEFT, sf::Keyboard::Key::Left);
    set(Key::MENU_RIGHT, sf::Keyboard::Key::Right);
}

std::string Input::getActionName(const Key action) {
    std::string ret;
    switch (action) {
        // Driving actions
        case Key::ACCELERATE:
            ret = "accelerate";
            break;
        case Key::BRAKE:
            ret = "brake";
            break;
        case Key::DRIFT:
            ret = "drift";
            break;
        case Key::TURN_LEFT:
            ret = "turn left";
            break;
        case Key::TURN_RIGHT:
            ret = "turn right";
            break;
        case Key::ITEM_FRONT:
            ret = "item front";
            break;
        case Key::ITEM_BACK:
            ret = "item back";
            break;
        // Menu actions
        case Key::PAUSE:
            ret = "pause";
            break;
        // [[ deprecated ]]
        // case Key::CONTINUE:
        //     ret = "continue";
        //     break;
        case Key::ACCEPT:
            ret = "accept";
            break;
        case Key::CANCEL:
            ret = "cancel";
            break;
        case Key::MENU_UP:
            ret = "menu up";
            break;
        case Key::MENU_DOWN:
            ret = "menu down";
            break;
        case Key::MENU_LEFT:
            ret = "menu left";
            break;
        case Key::MENU_RIGHT:
            ret = "menu right";
            break;
        default:
            ret = "?";
            break;
    }
    return ret;
}

// code based on:
// https://en.sfml-dev.org/forums/index.php?topic=15226.0
std::string Input::getKeyCodeName(const sf::Keyboard::Key keycode) {
    std::string ret;
    switch (keycode) {
        case sf::Keyboard::Key::A:
            ret = "a";
            break;
        case sf::Keyboard::Key::B:
            ret = "b";
            break;
        case sf::Keyboard::Key::C:
            ret = "c";
            break;
        case sf::Keyboard::Key::D:
            ret = "d";
            break;
        case sf::Keyboard::Key::E:
            ret = "e";
            break;
        case sf::Keyboard::Key::F:
            ret = "f";
            break;
        case sf::Keyboard::Key::G:
            ret = "g";
            break;
        case sf::Keyboard::Key::H:
            ret = "h";
            break;
        case sf::Keyboard::Key::I:
            ret = "i";
            break;
        case sf::Keyboard::Key::J:
            ret = "j";
            break;
        case sf::Keyboard::Key::K:
            ret = "k";
            break;
        case sf::Keyboard::Key::L:
            ret = "l";
            break;
        case sf::Keyboard::Key::M:
            ret = "m";
            break;
        case sf::Keyboard::Key::N:
            ret = "n";
            break;
        case sf::Keyboard::Key::O:
            ret = "o";
            break;
        case sf::Keyboard::Key::P:
            ret = "p";
            break;
        case sf::Keyboard::Key::Q:
            ret = "q";
            break;
        case sf::Keyboard::Key::R:
            ret = "r";
            break;
        case sf::Keyboard::Key::S:
            ret = "s";
            break;
        case sf::Keyboard::Key::T:
            ret = "t";
            break;
        case sf::Keyboard::Key::U:
            ret = "u";
            break;
        case sf::Keyboard::Key::V:
            ret = "v";
            break;
        case sf::Keyboard::Key::W:
            ret = "w";
            break;
        case sf::Keyboard::Key::X:
            ret = "x";
            break;
        case sf::Keyboard::Key::Y:
            ret = "y";
            break;
        case sf::Keyboard::Key::Z:
            ret = "z";
            break;
        case sf::Keyboard::Key::Num0:
            ret = "0";
            break;
        case sf::Keyboard::Key::Num1:
            ret = "1";
            break;
        case sf::Keyboard::Key::Num2:
            ret = "2";
            break;
        case sf::Keyboard::Key::Num3:
            ret = "3";
            break;
        case sf::Keyboard::Key::Num4:
            ret = "4";
            break;
        case sf::Keyboard::Key::Num5:
            ret = "5";
            break;
        case sf::Keyboard::Key::Num6:
            ret = "6";
            break;
        case sf::Keyboard::Key::Num7:
            ret = "7";
            break;
        case sf::Keyboard::Key::Num8:
            ret = "8";
            break;
        case sf::Keyboard::Key::Num9:
            ret = "9";
            break;
        case sf::Keyboard::Key::Escape:
            ret = "escape";
            break;
        case sf::Keyboard::Key::LControl:
            ret = "l ctrl";
            break;
        case sf::Keyboard::Key::LShift:
            ret = "l shift";
            break;
        case sf::Keyboard::Key::LAlt:
            ret = "l alt";
            break;
        case sf::Keyboard::Key::LSystem:
            ret = "l system";
            break;
        case sf::Keyboard::Key::RControl:
            ret = "r ctrl";
            break;
        case sf::Keyboard::Key::RShift:
            ret = "r shift";
            break;
        case sf::Keyboard::Key::RAlt:
            ret = "r alt";
            break;
        case sf::Keyboard::Key::RSystem:
            ret = "r system";
            break;
        case sf::Keyboard::Key::Dash:
            ret = "dash";
            break;
        case sf::Keyboard::Key::Space:
            ret = "space";
            break;
        case sf::Keyboard::Key::Enter:
            ret = "enter";
            break;
        case sf::Keyboard::Key::BackSpace:
            ret = "delete";
            break;
        case sf::Keyboard::Key::Tab:
            ret = "tab";
            break;
        case sf::Keyboard::Key::PageUp:
            ret = "pg up";
            break;
        case sf::Keyboard::Key::PageDown:
            ret = "pg down";
            break;
        case sf::Keyboard::Key::End:
            ret = "end";
            break;
        case sf::Keyboard::Key::Home:
            ret = "home";
            break;
        case sf::Keyboard::Key::Insert:
            ret = "insert";
            break;
        case sf::Keyboard::Key::Delete:
            ret = "delete";
            break;
        case sf::Keyboard::Key::Left:
            ret = "left";
            break;
        case sf::Keyboard::Key::Right:
            ret = "right";
            break;
        case sf::Keyboard::Key::Up:
            ret = "up";
            break;
        case sf::Keyboard::Key::Down:
            ret = "down";
            break;
        case sf::Keyboard::Key::Numpad0:
            ret = "numpad 0";
            break;
        case sf::Keyboard::Key::Numpad1:
            ret = "numpad 1";
            break;
        case sf::Keyboard::Key::Numpad2:
            ret = "numpad 2";
            break;
        case sf::Keyboard::Key::Numpad3:
            ret = "numpad 3";
            break;
        case sf::Keyboard::Key::Numpad4:
            ret = "numpad 4";
            break;
        case sf::Keyboard::Key::Numpad5:
            ret = "numpad 5";
            break;
        case sf::Keyboard::Key::Numpad6:
            ret = "numpad 6";
            break;
        case sf::Keyboard::Key::Numpad7:
            ret = "numpad 7";
            break;
        case sf::Keyboard::Key::Numpad8:
            ret = "numpad 8";
            break;
        case sf::Keyboard::Key::Numpad9:
            ret = "numpad 9";
            break;
        case sf::Keyboard::Key::F1:
            ret = "f1";
            break;
        case sf::Keyboard::Key::F2:
            ret = "f2";
            break;
        case sf::Keyboard::Key::F3:
            ret = "f3";
            break;
        case sf::Keyboard::Key::F4:
            ret = "f4";
            break;
        case sf::Keyboard::Key::F5:
            ret = "f5";
            break;
        case sf::Keyboard::Key::F6:
            ret = "f6";
            break;
        case sf::Keyboard::Key::F7:
            ret = "f7";
            break;
        case sf::Keyboard::Key::F8:
            ret = "f8";
            break;
        case sf::Keyboard::Key::F9:
            ret = "f9";
            break;
        case sf::Keyboard::Key::F10:
            ret = "f10";
            break;
        case sf::Keyboard::Key::F11:
            ret = "f11";
            break;
        case sf::Keyboard::Key::F12:
            ret = "f12";
            break;
        default:
            ret = "?";
            break;
    }
    return ret;
}