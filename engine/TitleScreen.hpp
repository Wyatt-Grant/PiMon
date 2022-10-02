#pragma once

#include <stdint.h>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"

using namespace picosystem;

class TitleScreen {       
    private:
        
    public:
        void draw(uint32_t tick);
        void update(uint32_t tick);
};