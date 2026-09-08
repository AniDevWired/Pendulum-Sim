/* Single Pendulum Sim*/

#include "raylib.h"
#include <math.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(void) {

    // window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PENDULUM SIM");
    SetTargetFPS(60);

    // pendulum
    int len = 0; // length of pendulum's rigid arm
    int radius = 30; // radius of pendulum's bob
    float angle = 0; // inital angle
    float angleV = 0.0; // angular vel
    float angleA = 0.0; // angular acc
    float gravity = 9.8; // gravity
    float mass = 0.9; // mass of bob
    float damping = 0.99; // damping
    Vector2 origin = {0,0}; // origin position
    Vector2 line = {0,0}; // line position
    Vector2 bob = {0,0}; // bob position

    bool isDrawing = false; // to draw line
    bool start = false; // to start calc

    // loop    
    while (!WindowShouldClose()) {

        Vector2 mousePos = GetMousePosition();

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isDrawing = true;

            if(!start) {
                origin = mousePos;
                line = mousePos;
            }
        }

        if(isDrawing) {
            line = mousePos;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                isDrawing = false;
                start = true;

                // calc angle between line and verticle axis
                float dx = line.x - origin.x; 
                float dy = line.y - origin.y;
                angle = atan2f(dx, dy);

                // calc length of line
                len = sqrt(pow((origin.x - line.x), 2) + pow((origin.y - line.y), 2));
            }
        }

        // main calc for pendulum
        if(start) {
            bob.x = len * sin(angle) + origin.x;
            bob.y = len * cos(angle) + origin.y;

            line.x = bob.x; line.y = bob.y;

            angleA = -mass*gravity*sin(angle)/len; // calc angular acc

            angleV += angleA;
            angleV *= damping;
            angle += angleV;
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawLineEx(origin, line, 4, BLACK);
            DrawLineEx((Vector2){origin.x-10, origin.y}, (Vector2) {origin.x+10, origin.y}, 4, BLACK);
            if(!(bob.x == 0 && bob.y == 0)) {
                DrawCircleV(bob, radius, SKYBLUE);
            }

            DrawText(TextFormat("len: %d", len), 10, 10, 24, BLACK);
            DrawText(TextFormat("bob.x | bob.y: %f %f", bob.x, bob.y), 10, 32, 24, BLACK);
            DrawText(TextFormat("origin.x | origin.y: %f %f", origin.x, origin.y), 10, 52, 24, BLACK);
            DrawText(TextFormat("line.x | line.y: %f %f", line.x, line.y), 10, 72, 24, BLACK);
            DrawText(TextFormat("angle: %f", angle*180/PI), 10, 92, 24, BLACK);

        EndDrawing();

    }

    CloseWindow();

    return 0;
}