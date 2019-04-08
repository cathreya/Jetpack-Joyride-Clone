#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"

#ifndef FIREB_H
#define FIREB_H



class FireBeam {
public:
    FireBeam() {}
    FireBeam(float yspeed, float x, float y, color_t color);
    glm::vec3 position;
    bounding_box_t bbox;
    bounding_box_t get_bbox();
    void draw(glm::mat4 VP);
    float rotation;
    int tick();
    void update_bbox();
    float yspeed;

private:
    VAO *object;
};

#endif 
