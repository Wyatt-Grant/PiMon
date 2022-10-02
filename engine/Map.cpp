#include "engine/Map.hpp"

#include "maps/town1/outside/town1_outside_tilemap.cpp"
#include "maps/town1/outside/town1_outside_tileset.cpp"

Map::Map() {
    offsetTileX = 0;
    offsetTileY = 0;
    movingOffsetX = 0;
    movingOffsetY = 0;
}

void Map::drawMapTile(const int16_t map[][80], int32_t x, int32_t y) {
    if (map[y+offsetTileY][x+offsetTileX] != -1) {
        sprite(map[y+offsetTileY][x+offsetTileX], (x * 8) + movingOffsetX - 12, (y * 8) + movingOffsetY - 12);
    }
}

void Map::drawMap(const int16_t below[][80], const int16_t above[][80]) {
    for (int y = 0; y <= 17; y++) {
        for (int x = 0; x <= 17; x++) {
            drawMapTile(below, x, y);
            drawMapTile(above, x, y);
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