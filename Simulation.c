#include <stdio.h>
#include <math.h>


typedef struct {
    double x;
    double y;
} Vector;


typedef struct {
    Vector position;
    Vector velocity;
    double mass;
} Body;


void updateBody(Body* body, Body* other, double dt) {
    double G = 6.67430e-11;  

    Vector r;
    r.x = other->position.x - body->position.x;
    r.y = other->position.y - body->position.y;

    double distance = sqrt(r.x*r.x + r.y*r.y);

    double force = G * body->mass * other->mass / (distance*distance);

    Vector acceleration;
    acceleration.x = force * r.x / (body->mass * distance);
    acceleration.y = force * r.y / (body->mass * distance);

    body->velocity.x += acceleration.x * dt;
    body->velocity.y += acceleration.y * dt;

    body->position.x += body->velocity.x * dt;
    body->position.y += body->velocity.y * dt;
}

int main() {
    Body body1 = {{0, 0}, {0, 0}, 1e24};  
    Body body2 = {{1e6, 0}, {0, 1e3}, 1e20};  

    double dt = 1;  // Time step in seconds
    for (int t = 0; t < 1e6; t += dt) {  
        updateBody(&body2, &body1, dt);
        printf("Time: %d s, Body2 Position: (%lf, %lf)\n", t, body2.position.x, body2.position.y);
    }

    return 0;
}
