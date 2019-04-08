#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"

#ifndef WALL_H
#define WALL_H



class Wall {
public:
    Wall() {}
    Wall(color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

#endif 
