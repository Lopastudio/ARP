#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <stdbool.h>

#define TILE_SIZE 32

extern Vector2 playerPosition;
extern Vector2 playerSize;
extern float   speed;

void CheckInputs(float dt);
void MovePlayer(Vector2 delta);
bool IsNearDoor(void);
bool IsSolid(int tile);

#endif