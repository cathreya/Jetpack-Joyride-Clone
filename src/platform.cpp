#include "platform.h"
#include "main.h"
#include <iostream>
using namespace std;

Platform::Platform(color_t color){
    float wid = WIDTH/2;
    float high = HEIGHT/2;
    this->position = glm::vec3(0, -20, 0);
    this->bbox.x = 0;
    this->bbox.y = -20;
    this->bbox.width = WIDTH;
    this->bbox.height = 0.02*high*2;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -1.0f*wid,0.0f*high,0.0,
         1.0f*wid,0.0f*high,0.0,
        -1.0f*wid,0.02f*high,0.0,
        
        -1.0f*wid,0.02f*high,0.0,
         1.0f*wid,0.0f*high,0.0,
         1.0f*wid,0.02f*high,0.0,

        // -wid,0.0f-10.0,0.0f,
        // wid,0.0f-10.0,0.0f,
        // -wid,10.0f-10.0,0.0f,
        // wid,0.0f-10.0,0.0f,
        // -wid,0.0f-10.0,0.0f,
        // wid,10.0f-10.0,0.0f,
        
        // 0.0f,high,0.0f,
        // wid,high,0.0f,
        // 0.0f,high-10.0f,0.0f,

        // wid,high,0.0f,
        // wid,high-10.0f,0.0f,
        // 0.0f,high-10.0f,0.0f,

    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Platform::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= (translate * rotate);
    Matrices.model *= translate ;

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}



bounding_box_t Platform::get_bbox() {
    return this->bbox;;
}

