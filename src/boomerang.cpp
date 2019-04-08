#include "boomerang.h"
#include "main.h"
#include <iostream>
using namespace std;


Boomerang::Boomerang(float x, float y, float xspeed, float yspeed, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 2;
    this->xspeed = xspeed;
    this->yspeed = yspeed;
    this->bbox.x = x;
    this->bbox.y = y;
    this->bbox.width = 2.0;
    this->bbox.height = 2.0;

    static const GLfloat vertex_buffer_data[] = {
        0,0.5,0,
        0,-0.5,0,
        -1,-1.7,0,

        0,0.5,0,
        0,-0.5,0,
        1,-1.7,0,

    };


    this->object = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, color, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    this->rotation+=2;
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


void Boomerang::set_xspeed(float x) {
    this->xspeed = x;
}
void Boomerang::set_yspeed(float x) {
    this->yspeed = x;
}

void Boomerang::move(float plus) {
    this->position.x -= plus;
    this->update_bbox();
}



bounding_box_t Boomerang::get_bbox() {
    return this->bbox;;
}

void Boomerang::update_bbox(){
    this->bbox.x = this->position.x;
    this->bbox.y = this->position.y;
}

void Boomerang::xforce(float a) {
    this->xspeed += a;
    // this->position.x += this->xspeed;
    this->update_bbox();
}

void Boomerang::tick() {
    this->position.x += this->xspeed;
    this->position.y += this->yspeed;

    this->update_bbox();
}

