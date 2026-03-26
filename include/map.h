#ifndef MAP_H
#define MAP_H

#include "raylib.h"

#define MAX_MAP 4096
#define TILE_SIZE 32

typedef enum
{
    TILE_GRASS = 0,
    TILE_DIRT = 1,
    TILE_CONCRETE = 2,
    TILE_BRICK = 3,
    TILE_FLOOR_WOOD = 4,
    TILE_STONE = 5,
    TILE_FLOOR_PVC = 6,
    TILE_DOOR = 7,
    TILE_SPAWN = 8,
    TILE_VOID = 9,
    TILE_END = 10,
    TILE_BOOBYTRAP = 11,
    TILE_LAVA = 12,
    TILE_COUNT
} TileID;

extern int map[MAX_MAP][MAX_MAP];
extern int MAP_WIDTH;
extern int MAP_HEIGHT;
extern Color tileColors[];

void LoadLevel(const char *file);
void DrawMap(void);
void TileInteraction(void);
int MapGet(int x, int y);
int MapWidth(void);
int MapHeight(void);

#endif