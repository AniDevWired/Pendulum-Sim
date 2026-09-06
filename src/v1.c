/* Single Pendulum Sim*/

#include "raylib.h"
#include <math.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Vector2 origin = {SCREEN_WIDTH/2.0f, 0};

int main(void) {

    // window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PENDULUM SIM");
    SetTargetFPS(60);

    // pendulum
    int len = 300; // length of pendulum's rigid arm
    int radius = 30; // radius of pendulum's bob
    float angle = PI/4.0f; // inital angle
    float angleV = 0.0; // angular vel
    float angleA = 0.0; // angular acc
    float gravity = 9.8; // gravity
    float mass = 0.40; // mass of bob
    Vector2 line = {0,0}; // line position
    Vector2 bob = {0,0}; // bob position


    // loop    
    while (!WindowShouldClose()) {

        bob.x = len * sin(angle) + origin.x;
        bob.y = len * cos(angle) + origin.y;

        line.x = bob.x; line.y = bob.y;

        angleA = -mass*gravity*sin(angle)/len; // calc angular acc

        angleV += angleA;
        angle += angleV;

        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawLineEx(origin, line, 7, BLACK);
            DrawCircleV(bob, radius, SKYBLUE);

        EndDrawing();

    }

    CloseWindow();

    return 0;
}