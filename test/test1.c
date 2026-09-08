/* COLLISON DETECTION */

#include "raylib.h"
#include <math.h>
#include "raymath.h"

#define MAX_BALL_NO 5

const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 800;

typedef struct Balls {  
    Vector2 positions[MAX_BALL_NO];
    Vector2 velocities[MAX_BALL_NO];
    float radii[MAX_BALL_NO];
    int masses[MAX_BALL_NO];
} Balls;

void checkEdgeCollision(Balls *ball, int idx);
void checkCollisonWithOtherBall(Balls *balls);

int main(void) {

    // window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "COLLISON DETECTION");
    SetTargetFPS(100);

    Balls balls;

    for (int i = 0; i < MAX_BALL_NO; i++) {
        balls.velocities[i] = (Vector2){GetRandomValue(10, 30), GetRandomValue(10, 30)};
        balls.masses[i] = GetRandomValue(2, 10);
        balls.radii[i] = sqrt(balls.masses[i]) * 20;
        balls.positions[i] = (Vector2){GetRandomValue(balls.radii[i]*2, GetScreenWidth()), GetRandomValue(balls.radii[i]*2, GetScreenHeight())};
    }
    
    while (!WindowShouldClose()) {

        float dt = GetFrameTime();

        for (int i = 0; i < MAX_BALL_NO; i++) {
            balls.positions[i] = Vector2Add(balls.positions[i], (Vector2){balls.velocities[i].x*dt*50, balls.velocities[i].y*dt*50});
            checkEdgeCollision(&balls, i);
        }

        checkCollisonWithOtherBall(&balls);
        
        BeginDrawing();
            
            ClearBackground(RAYWHITE);
            for (int i = 0; i < MAX_BALL_NO; i++) {
                DrawCircleV(balls.positions[i], balls.radii[i], SKYBLUE);
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void checkEdgeCollision(Balls *ball, int idx) {

    if(ball->positions[idx].x > GetScreenWidth() - ball->radii[idx]) {
        ball->positions[idx].x = GetScreenWidth() - ball->radii[idx];
        ball->velocities[idx].x *= -1;
    }

    if (ball->positions[idx].x < ball->radii[idx]) {
        ball->positions[idx].x = ball->radii[idx];
        ball->velocities[idx].x *= -1;
    }

    if (ball->positions[idx].y > GetScreenHeight() - ball->radii[idx]) {
        ball->positions[idx].y = GetScreenHeight() - ball->radii[idx];
        ball->velocities[idx].y *= -1;
    }

    if (ball->positions[idx].y < ball->radii[idx]) {
        ball->positions[idx].y = ball->radii[idx];
        ball->velocities[idx].y *= -1;
    }
}

void checkCollisonWithOtherBall(Balls *balls) {

    Vector2 normal = {0};

    for (int i = 0; i < MAX_BALL_NO; i++) {

        Vector2 ballAPos = balls->positions[i];
        Vector2 ballAVel = balls->velocities[i];
        float ballARadius = balls->radii[i];
        int m1 = balls->masses[i];

        for (int j = i+1; j < MAX_BALL_NO; j++) {

            Vector2 ballBPos = balls->positions[j];
            Vector2 ballBVel = balls->velocities[j];
            float ballBRadius = balls->radii[j];
            int m2 = balls->masses[j];
            
            Vector2 n = Vector2Subtract(ballBPos, ballAPos);
            float dist = Vector2Length(n);
            if(dist < ballARadius + ballBRadius) {

                // move apart if they overlap
                float depth = ballARadius + ballBRadius - dist;
                
                // manual normalization
                if(dist == 0.00) {
                    normal.x = 1.0f;
                    normal.y = 0.0f;
                } else {
                    normal.x = n.x/dist;
                    normal.y = n.y/dist; 
                }

                float moveDist = depth * 0.5;

                // move ballA opposite to direction of normal
                balls->positions[i].x -= normal.x * moveDist; // scaling up 
                balls->positions[i].y -= normal.y * moveDist; // scaling up

                // move ballB towards the direction of normal
                balls->positions[j].x += normal.x * moveDist; // scaling up 
                balls->positions[j].y += normal.y * moveDist; // scaling up

                // correct dist
                dist = ballARadius + ballBRadius;

                // tangent vector
                Vector2 tangent = {-normal.y, normal.x};

                // project velocities into normal and tangent vectors
                float v1n = Vector2DotProduct(normal, ballAVel);
                float v1t = Vector2DotProduct(tangent, ballAVel);
                float v2n = Vector2DotProduct(normal, ballBVel);
                float v2t = Vector2DotProduct(tangent, ballBVel);

                // calc normal velocity using 1D fomula
                float v1nPrime = (v1n * (m1 - m2) + 2.0f * m2 * v2n) / (m1 + m2);
                float v2nPrime = (v2n * (m2 - m1) + 2.0f * m1 * v1n) / (m1 + m2);

                // set velocity
                balls->velocities[i] = Vector2Add(Vector2Scale(normal, v1nPrime), Vector2Scale(tangent, v1t));
                balls->velocities[j] = Vector2Add(Vector2Scale(normal, v2nPrime), Vector2Scale(tangent, v2t));
            }
        }
    }
}