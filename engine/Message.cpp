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
    freeMessagesFromMemory(messages);
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
    freeMessagesFromMemory(messages);
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
            forceDrawMap = true;
            if (animY < 120 && MainScene != BATTLE) {
                animY += 4;
            } else {
                waiting = false;
                waitingForOpenAnimation = false;
                waitingForCloseAnimation = false;
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

void Message::draw(uint32_t tick) {
    if (waiting) {
        if (waitingForCloseAnimation || waitingForOpenAnimation) {
            drawWindow(animX, animY, animW, animH);
        } else {
            if (msgPtr != messages.end()) {
                drawWindow(0, 88, 120, 32);
                pen(themeR,themeG,themeB);
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
}