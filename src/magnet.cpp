#include "magnet.h"
#include "main.h"
#include <iostream>
#include <algorithm>
using namespace std;



Magnet::Magnet(float force, float x, float y, float* px, float* py, color_t color){
    this->position = glm::vec3(x, y, 0);
    this->bbox.x = x;
    this->bbox.y = y;
    this->bbox.width = 1;
    this->bbox.height = 1;
    this->rotation = 0;
    this->playerx = px;
    this->playery = py;
    this->force = force;


    static GLfloat g_vertex_buffer_data[500001];

    int vertices = 20;
    float curx = 0.0; 
    float cury = 1.0;

    float angle = 360.0/vertices;

    vertices = 10;
    angle *= M_PI/180;

    int i;
    for(i=0;i<9*vertices;i+=9){

        g_vertex_buffer_data[i] = 0.0;
        g_vertex_buffer_data[i+1] = 0.0;
        g_vertex_buffer_data[i+2] =0.0;
        
        g_vertex_buffer_data[i+3] = curx;
        g_vertex_buffer_data[i+4] = cury;
        g_vertex_buffer_data[i+5] = 0.0;


        float newx = curx*cos(angle) - cury*sin(angle);
        float newy = curx*sin(angle) + cury*cos(angle);

        swap(newx,curx);
        swap(newy,cury);
        
        g_vertex_buffer_data[i+6] = curx;
        g_vertex_buffer_data[i+7] = cury;
        g_vertex_buffer_data[i+8] = 0.0;
    }
    for(auto &j:g_vertex_buffer_data){
        j*=3;
    }

    float arr2[]= {
        0,3,0,
        3,3,0,
        3,1,0,

        0,3,0,
        3,1,0,
        0,1,0,

        0,-3,0,
        3,-3,0,
        3,-1,0,

        0,-3,0,
        3,-1,0,
        0,-1,0,
    };

    for(auto j:arr2){
        g_vertex_buffer_data[i] = j;
        i++;
    }


    this->object = create3DObject(GL_TRIANGLES, 3*(vertices+4), g_vertex_buffer_data, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 scale = glm::scale (glm::vec3(0.35,0.35,0.35));    // glTranslatef
    
    this->rotation = atan2((*this->playery - this->position.y),(*this->playerx - this->position.x));

    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate    = glm::rotate((float) (this->rotation), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate *scale);
    // Matrices.model *= translate ;

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}



bounding_box_t Magnet::get_bbox() {
    return this->bbox;;
}

void Magnet::move(float plus) {
    this->position.x -= plus;
    this->update_bbox();
}

void Magnet::update_bbox(){
    this->bbox.x = this->position.x;
    this->bbox.y = this->position.y;
}
