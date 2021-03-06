#include "shield.h"
#include "main.h"
#include <iostream>
using namespace std;


Shield::Shield(float x, float y, float xspeed, float yspeed, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 2;
    this->xspeed = xspeed;
    this->yspeed = yspeed;
    this->bbox.x = x;
    this->bbox.y = y;
    this->bbox.width = 1.0;
    this->bbox.height = 1.0;

    static const GLfloat vertex_buffer_data[] = {
        -2,2,0,
        -2,-2,0,
        2,-2,0,

        2,2,0,
        2,-2,0,
        -2,2,0,

        -2,-2,0,
        2,-2,0,
        0,-3,0,   
    };


    this->object = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, color, GL_FILL);
}

void Shield::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // this->rotation+=2;
    glm::mat4 scale = glm::scale (glm::vec3(0.35,0.35,0.35));    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


void Shield::set_xspeed(float x) {
    this->xspeed = x;
}
void Shield::set_yspeed(float x) {
    this->yspeed = x;
}

void Shield::move(float plus) {
    this->position.x -= plus;
    this->update_bbox();
}



bounding_box_t Shield::get_bbox() {
    return this->bbox;;
}

void Shield::update_bbox(){
    this->bbox.x = this->position.x;
    this->bbox.y = this->position.y;
}

void Shield::yforce(float a) {
    // if(a>0 && this->yspeed < YLIM){ 
    if(a>0){
        this->yspeed += a;
    }
    if(a <0 &&  this->yspeed > -YLIM ){
        this->yspeed += a;
    }
    // cout<<this->yspeed<<endl;
    this->position.y -= this->yspeed;
    // cout<<this->position.y<<endl;
    if(this->position.y > 20){
        // cout<<"above"<<endl;
        this->yspeed = 0;
        this->position.y = 20;
    }
    if(this->position.y < -15){
        // cout<<"below"<<endl;
        this->yspeed = 0;
        this->position.y = -15;   
    }
    this->update_bbox();
}

void Shield::tick() {
    this->position.x -= this->xspeed;
    this->position.y -= this->yspeed;

    this->update_bbox();
}

