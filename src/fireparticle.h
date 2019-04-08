#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"

#ifndef FIREP_H
#define FIREP_H



class FireParticle {
public:
    FireParticle() {}
    FireParticle(float x, float y, color_t color);
    glm::vec3 position;
    bounding_box_t bbox;
    bounding_box_t get_bbox();
    void draw(glm::mat4 VP);
    float rotation;
    void move(float );
    void update_bbox();

private:
    VAO *object;
};

#endif 
