#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"
#include "BaseMenu.hpp"

using namespace picosystem;

class Stats : public BaseMenu {
    public:
        Stats();
        void draw(uint32_t tick);
        void update(uint32_t tick);
};