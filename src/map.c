#include <stdio.h>
#include "../include/player.h"
#include "../include/map.h"


int map[MAX_MAP][MAX_MAP];
int MAP_WIDTH = 20;
int MAP_HEIGHT = 15;

Color tileColors[TILE_COUNT] = {
    [TILE_GRASS] = {100, 180, 80, 255},
    [TILE_DIRT] = {160, 114, 74, 255},
    [TILE_CONCRETE] = {176, 172, 164, 255},
    [TILE_BRICK] = {200, 152, 120, 255},
    [TILE_FLOOR_WOOD] = {200, 144, 80, 255},
    [TILE_STONE] = {136, 135, 128, 255},
    [TILE_FLOOR_PVC] = {216, 212, 200, 255},
    [TILE_DOOR] = {122, 72, 24, 255},
    [TILE_SPAWN] = {64, 224, 128, 255},
    [TILE_VOID] = {8, 8, 8, 255},
    [TILE_END] = {224, 192, 0, 255},
    [TILE_BOOBYTRAP] = {224, 64, 64, 255},
    [TILE_LAVA] = {204, 51, 0, 255},
};


void LoadLevel(const char *file)
{
    FILE *f = fopen(file, "r");
    if (!f)
        return;

    fscanf(f, "%d %d", &MAP_WIDTH, &MAP_HEIGHT);

    for (int row = 0; row < MAP_HEIGHT; row++)
    {
        for (int col = 0; col < MAP_WIDTH; col++)
        {
            fscanf(f, "%d", &map[row][col]);

            if (map[row][col] == TILE_SPAWN)
            {
                // center the player inside the spawn tile
                playerPosition.x = col * TILE_SIZE + TILE_SIZE / 2;
                playerPosition.y = row * TILE_SIZE + TILE_SIZE / 2;
            }
        }
    }

    fclose(f);
}

// nazov hovori sam za seba
void DrawMap(void)
{
    // draw tiles
    for (int row = 0; row < MAP_HEIGHT; row++)
    {
        for (int col = 0; col < MAP_WIDTH; col++)
        {
            int tileID = map[row][col];
            Color color = tileColors[tileID];
            int x = col * TILE_SIZE;
            int y = row * TILE_SIZE;

            DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, color);
        }
    }

    // draw grid
    Color gridColor = {0, 0, 0, 60};

    for (int col = 0; col <= MAP_WIDTH; col++)
        DrawLine(col * TILE_SIZE, 0, col * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, gridColor);

    for (int row = 0; row <= MAP_HEIGHT; row++)
        DrawLine(0, row * TILE_SIZE, MAP_WIDTH * TILE_SIZE, row * TILE_SIZE, gridColor);
}

// called on every frame ->>>>>> react to the tile the player is currently standing on
void TileInteraction(void)
{
    int tileX = (int)(playerPosition.x / TILE_SIZE);
    int tileY = (int)(playerPosition.y / TILE_SIZE);

    // ignore if somehow out of bounds
    bool outOfBounds = tileX < 0 || tileY < 0 || tileX >= MAP_WIDTH || tileY >= MAP_HEIGHT;
    if (outOfBounds)
        return;

    int tile = map[tileY][tileX];

    if (tile == TILE_LAVA || tile == TILE_VOID)
    {
        LoadLevel("level1.dat");
    }
    else if (tile == TILE_BOOBYTRAP)
    {
        map[tileY][tileX] = TILE_DIRT; // disarm boobytrap (we want boobytarps to only fire once)
        LoadLevel("level1.dat");
    }
}

// things for player.c
int MapGet(int x, int y) { return map[y][x]; }
int MapWidth(void) { return MAP_WIDTH; }
int MapHeight(void) { return MAP_HEIGHT; }