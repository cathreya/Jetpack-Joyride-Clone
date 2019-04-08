#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"

#ifndef RING_H
#define RING_H



class Ring {
public:
    Ring() {}
    Ring(float x, float y, color_t color);
    glm::vec3 position;
    bounding_box_t bbox;
    bounding_box_t get_bbox();
    void draw(glm::mat4 VP);
    float rotation;
    void move(float );
    void update_bbox();
    vector<float> pathx;
    vector<float> pathy;

    int cur;

private:
    VAO *object;
};

#endif 
