#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"

#ifndef SHIELD_H
#define SHIELD_H



class Shield {
public:
    Shield() {}
    Shield(float x, float y, float xspeed, float yspeed, color_t color);
    glm::vec3 position;
    bounding_box_t bbox;
    bounding_box_t get_bbox();
    void set_xspeed(float xsp);
    void set_yspeed(float ysp);
    void update_bbox();
    float rotation;
    void draw(glm::mat4 VP);
    void move(float plus);
    void yforce(float a);
    void tick();
    double xspeed;
    double yspeed;
private:
    VAO *object;
};

#endif // SLOW_H
