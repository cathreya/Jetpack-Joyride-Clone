#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"

#ifndef PLATFORM_H
#define PLATFORM_H



class Platform {
public:
    Platform() {}
    Platform(color_t color);
    glm::vec3 position;
    bounding_box_t bbox;
    bounding_box_t get_bbox();
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

#endif 
