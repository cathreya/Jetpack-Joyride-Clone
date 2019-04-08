#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"

#ifndef BOOM_H
#define BOOM_H



class Boomerang {
public:
    Boomerang() {}
    Boomerang(float x, float y, float xspeed, float yspeed, color_t color);
    glm::vec3 position;
    bounding_box_t bbox;
    bounding_box_t get_bbox();
    void set_xspeed(float xsp);
    void set_yspeed(float ysp);
    void update_bbox();
    float rotation;
    void draw(glm::mat4 VP);
    void move(float plus);
    void xforce(float a);
    void tick();
    double xspeed;
    double yspeed;
private:
    VAO *object;
};

#endif // SLOW_H
