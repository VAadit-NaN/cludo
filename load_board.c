#include <raylib.h>

int
main(void) {
    const int screenWidth = 1200;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "lewdo ;)");

    Texture2D map = LoadTexture("test_flattened.png");
    Vector2 ballPos = {347, 650};


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(map, screenWidth / 2 - map.width / 2, screenHeight / 2 - map.height / 2, WHITE);
        if (IsKeyDown(KEY_SPACE)) {
            ballPos = GetMousePosition();
        }
        DrawCircleV(ballPos, 20, MAROON);
        EndDrawing();
    }
}
