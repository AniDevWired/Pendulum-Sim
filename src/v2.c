/* Multiple Pendulum Sim*/

#include "raylib.h"
#include <complex.h>
#include <math.h>

#define MAX_PENDULUMS 10

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 700;
const int radius = 30;
const float gravity = 9.8;

Vector2 origin = {SCREEN_WIDTH/2.0f, 0};

typedef struct Pendulums{
    int lens[MAX_PENDULUMS];
    float angles[MAX_PENDULUMS];
    float anglesV[MAX_PENDULUMS];
    float anglesA[MAX_PENDULUMS];
    float masses[MAX_PENDULUMS];
    Vector2 lines[MAX_PENDULUMS];
    Vector2 bobs[MAX_PENDULUMS];
}Pendulums;


int main(void) {

    //window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Many Pendulum Sim");
    SetTargetFPS(60);

    // pendulums
    Pendulums pend;
    for(int i = 0; i < MAX_PENDULUMS; ++i) {
        pend.lens[i] = GetRandomValue(100, 590);
        pend.angles[i] = GetRandomValue(10, 90)*(PI/180.0f); // convert to radian
        pend.anglesV[i] = 0.0;
        pend.anglesA[i] = 0.0;
        pend.masses[i] = GetRandomValue(10, 100) / 100.0f;
        pend.lines[i] = (Vector2) {0,0};
        pend.bobs[i] = (Vector2) {0,0};
    }

    while (!WindowShouldClose()) {

        for(int i = 0; i < MAX_PENDULUMS; ++i) {
            pend.bobs[i].x = pend.lens[i] * sin(pend.angles[i]) + origin.x;
            pend.bobs[i].y = pend.lens[i] * cos(pend.angles[i]) + origin.y;

            pend.lines[i].x = pend.bobs[i].x;
            pend.lines[i].y = pend.bobs[i].y;

            pend.anglesA[i] = -pend.masses[i]*gravity * sin(pend.angles[i])/pend.lens[i];

            pend.anglesV[i] += pend.anglesA[i];
            pend.angles[i] += pend.anglesV[i];
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);
            for (int i = 0; i < MAX_PENDULUMS; ++i) {
                DrawLineEx(origin, pend.lines[i], 3, BLACK);
                DrawCircleV(pend.bobs[i], radius, SKYBLUE);
            }
        EndDrawing();
    }
    
    return 0;
}