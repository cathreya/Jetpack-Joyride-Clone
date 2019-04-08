#include "propulsion.h"
#include "main.h"
#include <iostream>
using namespace std;


Propulsion::Propulsion(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->yspeed = yspeed;

    float a = 0.2;    
    static GLfloat g_vertex_buffer_data[] = {
        a,-a,0,
        a,a,0,
        -a,a,0,

        a,-a,0,
        -a,-a,0,
        -a,a,0,        
    };

    // for(float &i:g_vertex_buffer_data){
    //     i *= 0.8;
    // }

    this->object = create3DObject(GL_TRIANGLES, 3*2, g_vertex_buffer_data, color, GL_FILL);
}

void Propulsion::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // this->rotation+=2;
    // glm::mat4 scale = glm::scale (glm::vec3(0.25,0.25,0.25));    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= (translate * scale);
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}



void Propulsion::move(float plus) {
    this->position.x -= plus;
    
}


void Propulsion::yforce(float a) {
    this->yspeed += a;
}

void Propulsion::tick() {
    this->position.y -= this->yspeed;
}

