#include "engine/Map.hpp"

Map::Map() {
    offsetTileX = 0;
    offsetTileY = 0;
    movingOffsetX = 0;
    movingOffsetY = 0;
}

void Map::drawMapTile(const int16_t map[][80], int32_t x, int32_t y) {
    if (map[y+offsetTileY][x+offsetTileX] != -1) {
        int16_t tile = map[y+offsetTileY][x+offsetTileX];
        // flowers
        if (time() % 2000 < 500) {
            if (tile == 18) tile = 20;
            if (tile == 19) tile = 21;
        } else if (time() % 2000 < 1000) {
            if (tile == 18) tile = 18;
            if (tile == 19) tile = 19;
        } else if (time() % 2000 < 1500) {
            if (tile == 18) tile = 22;
            if (tile == 19) tile = 23;
        }
        sprite(tile, (x * 8) + movingOffsetX - 12, (y * 8) + movingOffsetY - 12);
    }
}

void Map::drawMap(const int16_t below[][80], const int16_t above[][80]) {
    for (int y = 0; y <= 17; y++) {
        for (int x = 0; x <= 17; x++) {
            if (!menuOpen) {
                drawMapTile(below, x, y);
                drawMapTile(above, x, y);
            // } else if ((x > 8 && y < 13 && y > 9) || (x > 8 && x < 10)) {
            } else if ((y > 11) || (x > 8 && x < 10) || (x > 9 && y > 9 && y < 12)) { // only draw what you need to, when menus open this makes anaimtions smoother
                drawMapTile(below, x, y);
                drawMapTile(above, x, y);
            }
        }
    }
}

void Map::drawAboveMap(const int16_t above[][80]) {
    for (int y = 0; y <= 5; y++) {
        for (int x = 0; x <= 5; x++) {
            if (above[offsetTileY + y + 5][offsetTileX + x + 5] != -1) {
                drawMapTile(above, x + 5, y + 5);
            }
        }
    }
}

void Map::update(uint32_t tick) {
    offsetTileX  = -virtualCamera.x / 8;
    offsetTileY  = -virtualCamera.y / 8;
    movingOffsetX = virtualCamera.x % 8;
    movingOffsetY = virtualCamera.y % 8;
}

void Map::draw(uint32_t tick, int32_t mapNumber) {
    switch(mapNumber) {
        case 1:
            spritesheet(town_1_outside_tileset_buffer);
            drawMap(town1_outside_below, town1_outside_above);
            break;
    }
}

void Map::drawAbove(uint32_t tick, int32_t mapNumber) {
    switch(mapNumber) {
        case 1:
            spritesheet(town_1_outside_tileset_buffer);
            drawAboveMap(town1_outside_above);
            break;
    }
}