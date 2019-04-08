#include "ring.h"
#include "main.h"
#include <iostream>
#include <algorithm>
using namespace std;



Ring::Ring(float x, float y, color_t color){
    this->position = glm::vec3(x, y, 0);
    this->bbox.x = x-7;
    this->bbox.y = y;
    this->bbox.width = 1;
    this->bbox.height = 1;
    this->rotation = 0;
    this->cur = 0;

    static GLfloat g_vertex_buffer_data[500001];

    int vertices = 74;
    float curx = 1.0; 
    float cury = 0.0;

    float curx2 = 0.9; 
    float cury2 = 0.0;



    float angle = 360.0/vertices;

    angle *= M_PI/180;
    vertices /= 2;

    for(int i=0;i<9*2*vertices;i+=18){

        g_vertex_buffer_data[i]   =  curx2;
        g_vertex_buffer_data[i+1] =  cury2;
        g_vertex_buffer_data[i+2] =  -0.1;
        
        g_vertex_buffer_data[i+3] = curx;
        g_vertex_buffer_data[i+4] = cury;
        g_vertex_buffer_data[i+5] = -0.1;

        this->pathx.pb(4*(curx+curx2)+x);
        this->pathy.pb(4*(cury+cury2)+y);

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
        g_vertex_buffer_data[i+8] = -0.1;

        g_vertex_buffer_data[i+9]  =  newx2;
        g_vertex_buffer_data[i+10] =  newy2;
        g_vertex_buffer_data[i+11] =  -0.1;
        
        g_vertex_buffer_data[i+12] = curx;
        g_vertex_buffer_data[i+13] = cury;
        g_vertex_buffer_data[i+14] = -0.1; 

        g_vertex_buffer_data[i+15] = curx2;
        g_vertex_buffer_data[i+16] = cury2;
        g_vertex_buffer_data[i+17] = -0.1; 


    }
    for(auto &i:g_vertex_buffer_data){
        i*=8;
    }

    reverse(this->pathx.begin(), this->pathx.end());
    reverse(this->pathy.begin(), this->pathy.end());

    this->object = create3DObject(GL_TRIANGLES, 3*2*vertices, g_vertex_buffer_data, color, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef



    

    // this->rotation += 2;
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    // Matrices.model *= translate ;

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}



bounding_box_t Ring::get_bbox() {
    return this->bbox;;
}

void Ring::move(float plus) {
    this->position.x -= plus;
    this->update_bbox();
    for(int i=0;i<this->pathx.size();i++){
        this->pathx[i] -= plus;
        // cout<<i<<" "<<pathx[i]<<" , "<<pathy[i]<<endl;
    }
}

void Ring::update_bbox(){
    this->bbox.x = this->position.x-7;
    this->bbox.y = this->position.y;
}
