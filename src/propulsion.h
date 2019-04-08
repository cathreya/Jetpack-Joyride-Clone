#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"

#ifndef PROP_H
#define PROP_H



class Propulsion {
public:
    Propulsion() {}
    Propulsion(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void move(float plus);
    void yforce(float a);
    void tick();
    double yspeed;
private:
    VAO *object;
};

#endif // SLOW_H
