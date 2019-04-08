#include "dragon.h"
#include "main.h"
#include <iostream>
#include <algorithm>
using namespace std;



Dragon::Dragon(float x, float *py,  color_t color){
    this->position = glm::vec3(x, *py, 0);
    this->bbox.x = x-3;
    this->bbox.y = *py+5;
    this->bbox.width = 5;
    this->bbox.height = 5;
    this->rotation = -60;
    this->flag = 0;
    this->py = py;

    static GLfloat g_vertex_buffer_data[500001];

    int vertices = 30;
    float curx = 1.0; 
    float cury = 0.0;

    float curx2 = 0.8; 
    float cury2 = 0.0;



    float angle = 360.0/vertices;

    angle *= M_PI/180;
    vertices /= 2;
    int i = 0;
    for(i=0;i<9*3*vertices;i+=27){

        g_vertex_buffer_data[i]   =  curx2;
        g_vertex_buffer_data[i+1] =  cury2;
        g_vertex_buffer_data[i+2] =  0.3;
        
        g_vertex_buffer_data[i+3] = curx;
        g_vertex_buffer_data[i+4] = cury;
        g_vertex_buffer_data[i+5] = 0.3;


        float newx = curx*cos(angle) - cury*sin(angle);
        float newy = curx*sin(angle) + cury*cos(angle);
        
        float newx2 = curx2*cos(angle) - cury2*sin(angle);
        float newy2 = curx2*sin(angle) + cury2*cos(angle);


        swap(newx,curx);
        swap(newy,cury);
        
        swap(newx2,curx2);
        swap(newy2,cury2);
        

        g_vertex_buffer_data[i+6] = curx;
        g_vertex_buffer_data[i+7] = cury;
        g_vertex_buffer_data[i+8] = 0.3;

        g_vertex_buffer_data[i+9]  =  newx2;
        g_vertex_buffer_data[i+10] =  newy2;
        g_vertex_buffer_data[i+11] =  0.3;
        
        g_vertex_buffer_data[i+12] = curx;
        g_vertex_buffer_data[i+13] = cury;
        g_vertex_buffer_data[i+14] = 0.3; 

        g_vertex_buffer_data[i+15] = curx2;
        g_vertex_buffer_data[i+16] = cury2;
        g_vertex_buffer_data[i+17] = 0.3; 


        g_vertex_buffer_data[i+18]  =  newx;
        g_vertex_buffer_data[i+19] =  newy;
        g_vertex_buffer_data[i+20] =  0.3;
        
        g_vertex_buffer_data[i+21] = curx;
        g_vertex_buffer_data[i+22] = cury;
        g_vertex_buffer_data[i+23] = 0.3; 

        g_vertex_buffer_data[i+24] = newx-0.23;
        g_vertex_buffer_data[i+25] = newy+0.23;
        g_vertex_buffer_data[i+26] = 0.3; 



    }

    float vb2[] = {
        0,0,0,
        0.4,0,0,
        0.8,-1.5,0,

        0,0,0,
        0.4,-1.5,0,
        0,-1.5,0,

        -0.4,0,0,
        0,-1,0,
        0,0,0,

        -2,1,0,
        -0.4,0,0,
        0,-1,0,
        
        -2,-0.4,0,
        0,-1,0,
        -1,-0.4,0,
    };

    for(float j: vb2){
        if(i%3==0) j-= 2.7;
        g_vertex_buffer_data[i++] = j/3;
    }

    for(auto &i:g_vertex_buffer_data){
        i*=8;
    }

    this->object = create3DObject(GL_TRIANGLES, i/3, g_vertex_buffer_data, color, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    this->position.y = *this->py-4;
    this->update_bbox();
    // cout<<this->bbox.x<<" "<<this->bbox.y<<endl;
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef


    if(!flag){
        this->rotation -= 0.1;
        if(this->rotation <= -65) flag = 1;
    }
    else{
        this->rotation += 0.1;
        if(this->rotation >= -60) flag = 0;   
    }

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



bounding_box_t Dragon::get_bbox() {
    return this->bbox;;
}

void Dragon::move(float plus) {
    this->position.x -= plus;
    this->update_bbox();
}

void Dragon::update_bbox(){
    this->bbox.x = this->position.x-3;
    this->bbox.y = this->position.y+5;
}
