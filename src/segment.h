#include "main.h"

#ifndef DIGIT_H
#define DIGIT_H


class Segment
{
public:
    Segment() {}
    Segment(char c, float x, float y);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *object;
};

#endif // DIGIT_H
