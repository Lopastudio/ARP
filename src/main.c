#include "raylib.h"
#include "../include/player.h"
#include "../include/map.h"
#include <stdio.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define CAMERA_SMOOTH 3.0f
#define ZOOM_SPEED 0.1f
#define ZOOM_MIN 0.5f
#define ZOOM_MAX 4.0f
#define CAMERA_ZOOM 2.0f

static Camera2D camera = {0};

static void UpdateCam(float dt)
{
    // jemny pohyb kamery
    camera.target.x += (playerPosition.x - camera.target.x) * CAMERA_SMOOTH * dt;
    camera.target.y += (playerPosition.y - camera.target.y) * CAMERA_SMOOTH * dt;

    // scrollovanim zoomujes
    camera.zoom += GetMouseWheelMove() * ZOOM_SPEED;
    if (camera.zoom < ZOOM_MIN)
        camera.zoom = ZOOM_MIN;
    if (camera.zoom > ZOOM_MAX)
        camera.zoom = ZOOM_MAX;
}

static void DrawPlayer(void)
{
    int x = (int)(playerPosition.x - playerSize.x / 2);
    int y = (int)(playerPosition.y - playerSize.y / 2);
    DrawRectangle(x, y, (int)playerSize.x, (int)playerSize.y, ORANGE);
}

static void DrawHUD(void)
{
    DrawFPS(10, 10);
    DrawText(TextFormat("Pos: %.0f, %.0f", playerPosition.x, playerPosition.y), 10, 30, 16, GRAY);

    int tileX = (int)(playerPosition.x / TILE_SIZE);
    int tileY = (int)(playerPosition.y / TILE_SIZE);
    DrawText(TextFormat("Tile: %d, %d", tileX, tileY), 10, 45, 16, GRAY);
}

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "RPG");
    SetTargetFPS(240);

    LoadLevel("level1.dat");

    playerSize = (Vector2){TILE_SIZE, TILE_SIZE};

    camera.offset = (Vector2){WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f};
    camera.target = playerPosition;
    camera.rotation = 0.0f;
    camera.zoom = CAMERA_ZOOM;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        CheckInputs(dt);
        TileInteraction();
        UpdateCam(dt);

        // vykreslovanie
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);
        DrawMap();
        DrawPlayer();
        EndMode2D();

        DrawHUD();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}