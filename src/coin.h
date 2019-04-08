#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"

#ifndef COIN_H
#define COIN_H



class Coin {
public:
    Coin() {}
    Coin(int val, float x, float y, color_t color);
    glm::vec3 position;
    bounding_box_t bbox;
    bounding_box_t get_bbox();
    void draw(glm::mat4 VP);
    float rotation;
    void move(float );
    void update_bbox();
    int value;

private:
    VAO *object;
};

#endif 
