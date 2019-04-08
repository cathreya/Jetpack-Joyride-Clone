#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"

#ifndef MAG_H
#define MAG_H



class Magnet {
public:
    Magnet() {}
    Magnet(float force, float x, float y, float* px, float* py, color_t color);
    glm::vec3 position;
    bounding_box_t bbox;
    bounding_box_t get_bbox();
    void draw(glm::mat4 VP);
    float rotation;
    void move(float );
    void update_bbox();
    float force;

    float *playerx;
    float *playery;

private:
    VAO *object;
};

#endif 
