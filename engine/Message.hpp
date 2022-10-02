#pragma once

#include <regex>
#include <stdint.h>
#include <iterator>
#include "picosystem.hpp"

#include "types.hpp"
#include "globals.hpp"

using namespace picosystem;

class Message {       
    private:
        bool keepAlive;
        uint32_t messageOffset;
        std::vector<Text> messages;
        std::vector<Text>::iterator msgPtr;

        //animation
        bool waitingForOpenAnimation;
        bool waitingForCloseAnimation;
        int32_t animX;
        int32_t animY;
        int32_t animW;
        int32_t animH;
        
        void noCornerBox(int32_t x, int32_t y, int32_t w, int32_t h);
        void drawWindow(uint32_t x, uint32_t y, uint32_t w, uint32_t h);

    public:
        Message();
        void showMessages(std::vector<Text> messages);
        void showMessage(std::string msg);
        void draw(uint32_t tick);
        void update(uint32_t tick);
};