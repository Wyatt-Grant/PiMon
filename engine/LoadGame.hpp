#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"

using namespace picosystem;

class LoadGame {       
    private:
        int32_t menuIndex;

    public:
        LoadGame();
        void draw(uint32_t tick);
        void update(uint32_t tick);
};