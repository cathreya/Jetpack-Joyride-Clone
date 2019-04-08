#include "firebeam.h"
#include "main.h"
#include <iostream>
using namespace std;


FireBeam::FireBeam(float yspeed, float x, float y, color_t color){
    this->position = glm::vec3(x, y, 0);
    this->bbox.x = x;
    this->bbox.y = y;
    this->yspeed = yspeed;
    this->bbox.width = WIDTH;
    this->bbox.height = 1;
    this->rotation = 0;
    
    int wid =  WIDTH;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
       -1.0f*wid,0.5f,0.0,
         1.0f*wid,0.5f,0.0,
        -1.0f*wid,-0.5f,0.0,
        
        -1.0f*wid,-0.5f,0.0,
         1.0f*wid,-0.5f,0.0,
         1.0f*wid,0.5f,0.0,
    };


    this->object = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, color, GL_FILL);
}

void FireBeam::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // this->rotation += 2;
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    // Matrices.model *= translate ;

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}



bounding_box_t FireBeam::get_bbox() {
    return this->bbox;;
}

int FireBeam::tick(){
    this->position.y -= this->yspeed;
    this->update_bbox();
    // cout<<this->yspeed<<" "<<this->position.y<<endl;
    if(this->position.y <= max(-this->yspeed,this->yspeed) && this->position.y >= min(this->yspeed,-this->yspeed)){
        return 1;
    }
    return 0;
}

void FireBeam::update_bbox(){
    this->bbox.x = this->position.x;
    this->bbox.y = this->position.y;
}
