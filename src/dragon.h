#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"

#ifndef DRAG_H
#define DRAG_H



class Dragon {
public:
    Dragon() {}
    Dragon(float x, float *py, color_t color);
    glm::vec3 position;
    bounding_box_t bbox;
    bounding_box_t get_bbox();
    void draw(glm::mat4 VP);
    float rotation;
    void move(float );
    void update_bbox();

    float *py;
    int flag;

private:
    VAO *object;
};

#endif 
