#include "engine/Message.hpp"

Message::Message() {
    keepAlive = false;
    messageOffset = 1;
    waitingForOpenAnimation = false;
    waitingForCloseAnimation = false;
    animX = 0;
    animY = 0;
    animW = 0;
    animH = 0;
}

void Message::showMessage(std::string msg) {
    messages.clear();
    msg = std::regex_replace(msg, std::regex("PLAYER"), playerName);
    msg = std::regex_replace(msg, std::regex("RIVAL"), rivalName);
    messages.push_back({ msg, 0, []() -> void { return; } });

    msgPtr = messages.begin();
    waiting = true;
    keepAlive = true;
    waitingForOpenAnimation = true;
    waitingForCloseAnimation = false;
    messageOffset = 1;

    animX = 0;
    animY = 120;
    animW = 120;
    animH = 32;
}

void Message::showMessages(std::vector<Text> msgs) {
    messages.clear();
    for (auto &m : msgs) {
        m.text = std::regex_replace(m.text, std::regex("PLAYER"), playerName);
        m.text = std::regex_replace(m.text, std::regex("RIVAL"), rivalName);
        messages.push_back(m);
    }

    msgPtr = messages.begin();
    waiting = true;
    keepAlive = true;
    waitingForOpenAnimation = true;
    waitingForCloseAnimation = false;
    messageOffset = 1;

    animX = 0;
    animY = 120;
    animW = 120;
    animH = 32;
}

void Message::update(uint32_t tick) {
    if (waiting && !waitingForOpenAnimation && !waitingForCloseAnimation) {
        if (pressed(A) && msgPtr->text.length() == messageOffset) {
            if (++msgPtr == messages.end()) {
                waitingForCloseAnimation = true;
            } else {
                messageOffset = 1;
                keepAlive = true;
            }
        }
        if (messageOffset < msgPtr->text.length()) {
            messageOffset += 1;
        }
        if (pressed(A) && !keepAlive) {
            messageOffset = msgPtr->text.length();
        }
        if (messageOffset > 1) {
            keepAlive = false;
        }
    } else if (waiting) {
        if (waitingForCloseAnimation) {
            if (animY < 120 && MainScene != BATTLE) {
                animY += 4;
            } else {
                waiting = false;
                waitingForOpenAnimation = false;
                msgPtr--;
                msgPtr->callback();
            }
        } else if (waitingForOpenAnimation) {
            if (animY > 88 && MainScene != BATTLE) {
                animY -= 4;
            } else {
                waitingForOpenAnimation = false;
            }
        }
    }
}

void Message::noCornerBox(int32_t x, int32_t y, int32_t w, int32_t h) {
    hline(x+1, y,   w-2);
    hline(x+1, y+h-1, w-2);
    vline(x, y+1,   h-2);
    vline(x+w-1, y+1, h-2);
}

void Message::drawWindow(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    pen(15,15,15);
    noCornerBox(x,y,w,h);
    frect(x+1,y+1,w-2,h-2);
    pen(3,3,3);
    noCornerBox(x+1,y+1,w-2,h-2);
}

void Message::draw(uint32_t tick) {
    if (waiting) {
        if (waitingForCloseAnimation || waitingForOpenAnimation) {
            drawWindow(animX, animY, animW, animH);
        } else {
            drawWindow(0, 88, 120, 32);
            pen(0, 0, 0);
            text(msgPtr->text.substr(0, messageOffset), 4, 92, 108);

            if (messageOffset == msgPtr->text.length()) {
                uint32_t cursorOffset = (time() % 600 < 300) ? 111 : 110;
                hline(106, cursorOffset, 8);
                hline(107, cursorOffset+1, 6);
                hline(108, cursorOffset+2, 4);
                hline(109, cursorOffset+3, 2);
            }
        }
    }
}