#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"

#ifndef BALL_H
#define BALL_H



class Ball {
public:
    Ball() {}
    Ball(float x, float y, float xspeed, float yspeed, color_t color);
    glm::vec3 position;
    bounding_box_t bbox;
    bounding_box_t get_bbox();
    void set_xspeed(float xsp);
    void set_yspeed(float ysp);
    void update_bbox();
    float rotation;
    void draw(glm::mat4 VP);
    int set_position(float x, float y);
    int move(float plus);
    void jump();
    void tick();
    void yforce(float a);
    void xforce(float a);
    void resetForce();
    void shield();
    void reset();
    double xspeed;
    double yspeed;
private:
    VAO *object;
};

#endif // BALL_H
