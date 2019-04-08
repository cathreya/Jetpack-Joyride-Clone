#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"

#ifndef SWORD_H
#define SWORD_H



class Sword {
public:
    Sword() {}
    Sword(float x, float y, float *px, float *py, color_t color);
    glm::vec3 position;
    bounding_box_t bbox;
    bounding_box_t get_bbox();
    void update_bbox();
    float rotation;
    void draw(glm::mat4 VP);
    void move(float plus);
    int flag;
    float *px,*py;
private:
    VAO *object;
};

#endif // SLOW_H
