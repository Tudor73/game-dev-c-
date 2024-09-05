#include "player.h"

Player::Player(int name) { this->name = name; }

std::string Player::PlayerToString() { return std::to_string(this->name); }