#pragma once
#include <string>

class Player {
  public:
    int name;
    Player(int name);

    std::string PlayerToString();
};