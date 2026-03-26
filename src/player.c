#include "../include/player.h"
#include "../include/map.h"
#include "raylib.h"

Vector2 playerPosition;
Vector2 playerSize;
float speed = 200.0f;


// true if tile at position (this one line lower) blocks movement
static bool TileIsWalkable(int tileX, int tileY)
{
    int tile = MapGet(tileX, tileY);
    return !IsSolid(tile);
}

// try to move the player on X. Stop ifa  solid tile is in the way
static void MovePlayerX(float deltaX)
{
    float newX = playerPosition.x + deltaX;
    int tileX  = (int)(newX              / TILE_SIZE);
    int tileY  = (int)(playerPosition.y  / TILE_SIZE);

    if (TileIsWalkable(tileX, tileY))
        playerPosition.x = newX;
}

// try to move the player on Y. Stop if a solid tile is in the way
static void MovePlayerY(float deltaY)
{
    float newY = playerPosition.y + deltaY;
    int tileX  = (int)(playerPosition.x / TILE_SIZE);
    int tileY  = (int)(newY             / TILE_SIZE);

    if (TileIsWalkable(tileX, tileY))
        playerPosition.y = newY;
}

// moving of player (this function is for checking colisions.)
void MovePlayer(Vector2 delta)
{
    MovePlayerX(delta.x);
    MovePlayerY(delta.y);
}


// returns true if you cant move on a tile
bool IsSolid(int tile)
{
    return tile == TILE_STONE || tile == TILE_BRICK;
}

// is true only if a door is in 3x3 area around player
bool IsNearDoor(void)
{
    int playerTileX = (int)(playerPosition.x / TILE_SIZE);
    int playerTileY = (int)(playerPosition.y / TILE_SIZE);

    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            int checkX = playerTileX + dx;
            int checkY = playerTileY + dy;

            bool inBounds = checkX >= 0 && checkY >= 0
                         && checkX < MapWidth() && checkY < MapHeight();

            if (inBounds && MapGet(checkX, checkY) == TILE_DOOR)
                return true;
        }
    }

    return false;
}


void CheckInputs(float dt)
{
    Vector2 move = { 0.0f, 0.0f };

    if (IsKeyDown(KEY_W)) move.y -= speed * dt;
    if (IsKeyDown(KEY_S)) move.y += speed * dt;
    if (IsKeyDown(KEY_A)) move.x -= speed * dt;
    if (IsKeyDown(KEY_D)) move.x += speed * dt;

    MovePlayer(move);

    if (IsKeyPressed(KEY_E) && IsNearDoor())
        LoadLevel("level2.dat");
}