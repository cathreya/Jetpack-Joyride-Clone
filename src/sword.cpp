#include "sword.h"
#include "main.h"
#include <iostream>
using namespace std;


Sword::Sword(float x, float y, float *px, float *py, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->bbox.x = x+2;
    this->bbox.y = y;
    this->bbox.width = 4.5;
    this->bbox.height = 1.0;
    this->flag = 2;

    this->px = px;
    this->py = py;

    static const GLfloat vertex_buffer_data[] = {
        0,0.5,0,
        0,-0.5,0,
        4,-0.5,0,

        4,-0.5,0,
        4,0.5,0,
        0,0.5,0,

        1,2,0,
        1.5,-2,0,
        1,-2,0,

        1,2,0,
        1.5,2,0,
        1.5,-2,0,

        4,-0.5,0,
        4,0.5,0,
        4.5,0,0,

    };


    this->object = create3DObject(GL_TRIANGLES, 5*3, vertex_buffer_data, color, GL_FILL);
}

void Sword::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    
    if(flag != 2){
        this->position.x = *px + 1;
        this->position.y = *py;
        this->update_bbox();
    }

    glm::mat4 translate = glm::translate (this->position);    // glTranslatef

    if(flag==1){
        this->rotation -= 1;
        if(this->rotation <= -20) flag = 0;
    }
    else if(flag ==0){
        this->rotation += 1;
        if(this->rotation >= 20) flag = 1;   
    }
    // glm::mat4 scale = glm::scale (glm::vec3(0.35,0.35,0.35));    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= (translate * scale);
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


void Sword::move(float plus) {
    this->position.x -= plus;
    this->update_bbox();
}



bounding_box_t Sword::get_bbox() {
    return this->bbox;;
}

void Sword::update_bbox(){
    this->bbox.x = this->position.x+2;
    this->bbox.y = this->position.y;
}


