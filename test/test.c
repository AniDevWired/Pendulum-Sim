/* MOUSE DRAG TEST */

#include "raylib.h"

int main() {
    InitWindow(800, 600, "Drag testtttt");
    SetTargetFPS(60);

    Vector2 circleCenter = { 400.0f, 300.0f };
    float circleRadius = 50.0f;
    bool isDragging = false;

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointCircle(mousePos, circleCenter, circleRadius)) {
                isDragging = true;
            }
        }

        if (isDragging) {
            Vector2 delta = GetMouseDelta();
            circleCenter.x += delta.x;
            circleCenter.y += delta.y;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                isDragging = false;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircleV(circleCenter, circleRadius, isDragging ? RED : BLUE);
        DrawText("Click and drag the circle", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
