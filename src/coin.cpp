#include "coin.h"
#include "main.h"
#include <iostream>
using namespace std;

void swap(float &a, float &b){
    float c = a;
    a = b;
    b = c;
}
#define PI 3.14159265

Coin::Coin(int value, float x, float y, color_t color){
    this->position = glm::vec3(x, y, 0);
    this->bbox.x = x;
    this->bbox.y = y;
    this->bbox.width = 1;
    this->bbox.height = 1;
    this->rotation = 0;
    this->value = value;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    // static const GLfloat vertex_buffer_data[] = {
    //    -0.5,0.5,0.0,
    //     0.5,0.5,0.0,
    //     0.5,-0.5,0.0,

    //     0.5,-0.5,0.0,
    //    -0.5,0.5,0.0,
    //     -0.5,-0.5,0.0,
    // };

    static GLfloat g_vertex_buffer_data[500001];

    int vertices = 6;
    float curx = 0.0; 
    float cury = 1.0;

    float angle = 360.0/vertices;

    angle *= PI/180;

    for(int i=0;i<9*vertices;i+=9){

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
    for(auto &i:g_vertex_buffer_data){
        i*=0.5;
    }


    this->object = create3DObject(GL_TRIANGLES, 9*vertices, g_vertex_buffer_data, color, GL_FILL);
}

void Coin::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    this->rotation += 2;
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    // Matrices.model *= translate ;

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}



bounding_box_t Coin::get_bbox() {
    return this->bbox;;
}

void Coin::move(float plus) {
    this->position.x -= plus;
    this->update_bbox();
}

void Coin::update_bbox(){
    this->bbox.x = this->position.x;
    this->bbox.y = this->position.y;
}
