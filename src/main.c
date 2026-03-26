#include "raylib.h"

static Vector2 playerPosition;
static float speed = 200.0f;

void checkInputs(void) {
    float dt = GetFrameTime();
    if (IsKeyDown(KEY_W)) playerPosition.y -= speed * dt;
    if (IsKeyDown(KEY_A)) playerPosition.x -= speed * dt;
    if (IsKeyDown(KEY_S)) playerPosition.y += speed * dt;
    if (IsKeyDown(KEY_D)) playerPosition.x += speed * dt;
}

int main(void)
{
    const int screenWidth  = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib");
    playerPosition = (Vector2){ (float)screenWidth/2, (float)screenHeight/2 };
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        checkInputs();
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Hello from raylib!", 190, 200, 20, LIGHTGRAY);
            DrawCircleV(playerPosition, 10, ORANGE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}