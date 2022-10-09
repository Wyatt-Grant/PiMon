#include "engine/Teleporter.hpp"

Teleporter::Teleporter() {
    teleportTimer = 0;
    teleporting = false;
    nextPlayerDir = down;
    nextPos = {0,0};
    nextMap = 1;
}

void Teleporter::teleport(uint32_t newMap, int32_t newX, int32_t newY, Direction dir) {
    blend(ALPHA);
    nextMap = newMap;
    nextPos = {newX, newY};
    nextPlayerDir = dir;
    teleporting = true;
}

void Teleporter::update(uint32_t tick) {
    //player house
    if(virtualCamera.x == -80 && virtualCamera.y == -64 && currentMap == 1) {
        teleport(0, -64, -270, up);
    }
    if(virtualCamera.x == -64 && virtualCamera.y == -272 && currentMap == 0) {
        teleport(1, -80, -66, down);
    }

    //player room
    if(virtualCamera.x == -96 && virtualCamera.y == -176 && currentMap == 0) {
        teleport(0, -240, -178, down);
    }
    if(virtualCamera.x == -240 && virtualCamera.y == -176 && currentMap == 0) {
        teleport(0, -96, -178, down);
    }

    //rival house
    if(virtualCamera.x == -208 && virtualCamera.y == -64 && currentMap == 1) {
        teleport(0, -64, -94, up);
    }
    if(virtualCamera.x == -64 && virtualCamera.y == -96 && currentMap == 0) {
        teleport(1, -208, -66, down);
    }

    //rival room
    if(virtualCamera.x == -96 && virtualCamera.y == 0 && currentMap == 0) {
        teleport(0, -240, -2, down);
    }
    if(virtualCamera.x == -240 && virtualCamera.y == 0 && currentMap == 0) {
        teleport(0, -96, -2, down);
    }

    //lab
    if(virtualCamera.x == -176 && virtualCamera.y == -160 && currentMap == 1) {
        teleport(0, -32, -462, up);
    }
    if(virtualCamera.x == -32 && virtualCamera.y == -464 && currentMap == 0) {
        teleport(1, -176, -162, down);
    }
}

void Teleporter::draw(uint32_t tick, Player *player) {
    if (teleporting) {
        teleportTimer += 1;
        if (teleportTimer == teleportTime/2) {
            currentMap = nextMap;
            virtualCamera = nextPos;
            player->direction = nextPlayerDir;
        }
        if (teleportTimer == teleportTime) {
            teleporting = false;
            teleportTimer = 0;
            blend(MASK);
        } else {
            pen(0, 0, 0, teleportTimer*2); // adjust with tele time
            frect(0,0,120,120);
        }
    }
}