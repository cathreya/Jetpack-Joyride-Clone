#include "ball.h"
#include "main.h"
#include <iostream>
using namespace std;


Ball::Ball(float x, float y, float xspeed, float yspeed, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->xspeed = xspeed;
    this->yspeed = yspeed;
    this->bbox.x = x;
    this->bbox.y = y-2;
    this->bbox.width = 1.0;
    this->bbox.height = 6;


    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    // static const GLfloat vertex_buffer_data[] = {
    //     1,1,0,
    //     -1,1,0,
    //     1,-1,0,

    //     -1,1,0,
    //     1,-1,0,
    //     -1,-1,0,

    // };
    static const GLfloat vertex_buffer_data[] = {
        0,-1.5,0,
        0.25,1.5,0,
        -0.5,-1.5,0,

        -0.25,1.5,0,
        0.25,1.5,0,
        -0.5,-1.5,0,

        0.25,1.5,0,
        0.75,1.5,0,
        0.5,-1.5,0,

        0.5,-1.5,0,
        0,-1.5,0,
        0.25,1.5,0,

        0.5,-1.5,0,
        0,-1.5,0,
        0.25, -5, 0,

        0.25, -5, 0,
        0.25, -4.5, 0,
        1, -5, 0,
        


        0.25,1.75,0,
        0.25,3,0,
        1,3,0,
        
        1,3,0,
        1,1.75,0,
        0.25,1.75,0,

    };
    color_t white = {255,222,173};
    color_t white2 = {220,20,60};
    color_t white3 = {0,0,128};
    static const GLfloat g_color_buffer_data[] = {
        (float)COLOR_DARK_BLUE.r/256.0f , (float)COLOR_DARK_BLUE.g/256.0f, (float)COLOR_DARK_BLUE.b/256.0f,
        (float)COLOR_DARK_BLUE.r/256.0f , (float)COLOR_DARK_BLUE.g/256.0f, (float)COLOR_DARK_BLUE.b/256.0f,
        (float)COLOR_DARK_BLUE.r/256.0f , (float)COLOR_DARK_BLUE.g/256.0f, (float)COLOR_DARK_BLUE.b/256.0f,
        
        (float)COLOR_DARK_BLUE.r/256.0f , (float)COLOR_DARK_BLUE.g/256.0f, (float)COLOR_DARK_BLUE.b/256.0f,
        (float)COLOR_DARK_BLUE.r/256.0f , (float)COLOR_DARK_BLUE.g/256.0f, (float)COLOR_DARK_BLUE.b/256.0f,
        (float)COLOR_DARK_BLUE.r/256.0f , (float)COLOR_DARK_BLUE.g/256.0f, (float)COLOR_DARK_BLUE.b/256.0f,
        
        (float)white.r/256.0f , (float)white.g/256.0f, (float)white.b/256.0f,
        (float)white.r/256.0f , (float)white.g/256.0f, (float)white.b/256.0f,
        (float)white.r/256.0f , (float)white.g/256.0f, (float)white.b/256.0f,
        
        (float)white2.r/256.0f , (float)white2.g/256.0f, (float)white2.b/256.0f,
        (float)white2.r/256.0f , (float)white2.g/256.0f, (float)white2.b/256.0f,
        (float)white2.r/256.0f , (float)white2.g/256.0f, (float)white2.b/256.0f,
        
        (float)white3.r/256.0f , (float)white3.g/256.0f, (float)white3.b/256.0f,
        (float)white3.r/256.0f , (float)white3.g/256.0f, (float)white3.b/256.0f,
        (float)white3.r/256.0f , (float)white3.g/256.0f, (float)white3.b/256.0f,
        
        0,0,0,
        0,0,0,
        0,0,0,
        
        0,0,0,
        0,0,0,
        0,0,0,

        (float)white.r/256.0f , (float)white.g/256.0f, (float)white.b/256.0f,
        (float)white.r/256.0f , (float)white.g/256.0f, (float)white.b/256.0f,
        (float)white.r/256.0f , (float)white.g/256.0f, (float)white.b/256.0f,
        

    };

    this->object = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data, g_color_buffer_data, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 1));
    glm::mat4 scale = glm::scale (glm::vec3(0.75,0.75,0.75));    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

int Ball::set_position(float x, float y) {
    if(x > 10){
        return 1;
    }
    this->position = glm::vec3(x, y, 0);
    this->update_bbox();
    return 0;
}

void Ball::set_xspeed(float x) {
    this->xspeed = x;
}
void Ball::set_yspeed(float x) {
    this->yspeed = x;
}

int Ball::move(float plus) {
    this->position.x -= plus;
    int ret = 0;
    if(this->position.x > 10.0){
        this->position.x = 10.0;
        ret = 1;
    }
    if(this->position.x < -20.0){
        this->position.x = -20.0;

    }
    this->update_bbox();
    return ret;
}

void Ball::jump() {
    this->position.y += 0.2;
    this->update_bbox();
}

void Ball::shield(){
        static const GLfloat vertex_buffer_data[] = {
        0,-1.5,0,
        0.25,1.5,0,
        -0.5,-1.5,0,

        -0.25,1.5,0,
        0.25,1.5,0,
        -0.5,-1.5,0,

        0.25,1.5,0,
        0.75,1.5,0,
        0.5,-1.5,0,

        0.5,-1.5,0,
        0,-1.5,0,
        0.25,1.5,0,

        0.5,-1.5,0,
        0,-1.5,0,
        0.25, -5, 0,

        0.25, -5, 0,
        0.25, -4.5, 0,
        1, -5, 0,
        


        0.25,1.75,0,
        0.25,3,0,
        1,3,0,
        
        1,3,0,
        1,1.75,0,
        0.25,1.75,0,

    };
    color_t white = {255,222,173};
    color_t white2 = COLOR_GREEN;
    color_t white3 = COLOR_GREEN;
    static const GLfloat g_color_buffer_data[] = {
        (float)COLOR_DARK_BLUE.r/256.0f , (float)COLOR_DARK_BLUE.g/256.0f, (float)COLOR_DARK_BLUE.b/256.0f,
        (float)COLOR_DARK_BLUE.r/256.0f , (float)COLOR_DARK_BLUE.g/256.0f, (float)COLOR_DARK_BLUE.b/256.0f,
        (float)COLOR_DARK_BLUE.r/256.0f , (float)COLOR_DARK_BLUE.g/256.0f, (float)COLOR_DARK_BLUE.b/256.0f,
        
        (float)COLOR_DARK_BLUE.r/256.0f , (float)COLOR_DARK_BLUE.g/256.0f, (float)COLOR_DARK_BLUE.b/256.0f,
        (float)COLOR_DARK_BLUE.r/256.0f , (float)COLOR_DARK_BLUE.g/256.0f, (float)COLOR_DARK_BLUE.b/256.0f,
        (float)COLOR_DARK_BLUE.r/256.0f , (float)COLOR_DARK_BLUE.g/256.0f, (float)COLOR_DARK_BLUE.b/256.0f,
        
        (float)white.r/256.0f , (float)white.g/256.0f, (float)white.b/256.0f,
        (float)white.r/256.0f , (float)white.g/256.0f, (float)white.b/256.0f,
        (float)white.r/256.0f , (float)white.g/256.0f, (float)white.b/256.0f,
        
        (float)white2.r/256.0f , (float)white2.g/256.0f, (float)white2.b/256.0f,
        (float)white2.r/256.0f , (float)white2.g/256.0f, (float)white2.b/256.0f,
        (float)white2.r/256.0f , (float)white2.g/256.0f, (float)white2.b/256.0f,
        
        (float)white3.r/256.0f , (float)white3.g/256.0f, (float)white3.b/256.0f,
        (float)white3.r/256.0f , (float)white3.g/256.0f, (float)white3.b/256.0f,
        (float)white3.r/256.0f , (float)white3.g/256.0f, (float)white3.b/256.0f,
        
        (float)COLOR_GREEN.r/256.0f , (float)COLOR_GREEN.g/256.0f, (float)COLOR_GREEN.b/256.0f,
        (float)COLOR_GREEN.r/256.0f , (float)COLOR_GREEN.g/256.0f, (float)COLOR_GREEN.b/256.0f,
        (float)COLOR_GREEN.r/256.0f , (float)COLOR_GREEN.g/256.0f, (float)COLOR_GREEN.b/256.0f,
        
        (float)COLOR_GREEN.r/256.0f , (float)COLOR_GREEN.g/256.0f, (float)COLOR_GREEN.b/256.0f,
        (float)COLOR_GREEN.r/256.0f , (float)COLOR_GREEN.g/256.0f, (float)COLOR_GREEN.b/256.0f,
        (float)COLOR_GREEN.r/256.0f , (float)COLOR_GREEN.g/256.0f, (float)COLOR_GREEN.b/256.0f,

        (float)white.r/256.0f , (float)white.g/256.0f, (float)white.b/256.0f,
        (float)white.r/256.0f , (float)white.g/256.0f, (float)white.b/256.0f,
        (float)white.r/256.0f , (float)white.g/256.0f, (float)white.b/256.0f,
        

    };

    this->object = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data, g_color_buffer_data, GL_FILL);
}

void Ball::reset(){
        static const GLfloat vertex_buffer_data[] = {
        0,-1.5,0,
        0.25,1.5,0,
        -0.5,-1.5,0,

        -0.25,1.5,0,
        0.25,1.5,0,
        -0.5,-1.5,0,

        0.25,1.5,0,
        0.75,1.5,0,
        0.5,-1.5,0,

        0.5,-1.5,0,
        0,-1.5,0,
        0.25,1.5,0,

        0.5,-1.5,0,
        0,-1.5,0,
        0.25, -5, 0,

        0.25, -5, 0,
        0.25, -4.5, 0,
        1, -5, 0,
        


        0.25,1.75,0,
        0.25,3,0,
        1,3,0,
        
        1,3,0,
        1,1.75,0,
        0.25,1.75,0,

    };
    color_t white = {255,222,173};
    color_t white2 = {220,20,60};
    color_t white3 = {0,0,128};
    static const GLfloat g_color_buffer_data[] = {
        (float)COLOR_DARK_BLUE.r/256.0f , (float)COLOR_DARK_BLUE.g/256.0f, (float)COLOR_DARK_BLUE.b/256.0f,
        (float)COLOR_DARK_BLUE.r/256.0f , (float)COLOR_DARK_BLUE.g/256.0f, (float)COLOR_DARK_BLUE.b/256.0f,
        (float)COLOR_DARK_BLUE.r/256.0f , (float)COLOR_DARK_BLUE.g/256.0f, (float)COLOR_DARK_BLUE.b/256.0f,
        
        (float)COLOR_DARK_BLUE.r/256.0f , (float)COLOR_DARK_BLUE.g/256.0f, (float)COLOR_DARK_BLUE.b/256.0f,
        (float)COLOR_DARK_BLUE.r/256.0f , (float)COLOR_DARK_BLUE.g/256.0f, (float)COLOR_DARK_BLUE.b/256.0f,
        (float)COLOR_DARK_BLUE.r/256.0f , (float)COLOR_DARK_BLUE.g/256.0f, (float)COLOR_DARK_BLUE.b/256.0f,
        
        (float)white.r/256.0f , (float)white.g/256.0f, (float)white.b/256.0f,
        (float)white.r/256.0f , (float)white.g/256.0f, (float)white.b/256.0f,
        (float)white.r/256.0f , (float)white.g/256.0f, (float)white.b/256.0f,
        
        (float)white2.r/256.0f , (float)white2.g/256.0f, (float)white2.b/256.0f,
        (float)white2.r/256.0f , (float)white2.g/256.0f, (float)white2.b/256.0f,
        (float)white2.r/256.0f , (float)white2.g/256.0f, (float)white2.b/256.0f,
        
        (float)white3.r/256.0f , (float)white3.g/256.0f, (float)white3.b/256.0f,
        (float)white3.r/256.0f , (float)white3.g/256.0f, (float)white3.b/256.0f,
        (float)white3.r/256.0f , (float)white3.g/256.0f, (float)white3.b/256.0f,
        
        0,0,0,
        0,0,0,
        0,0,0,
        
        0,0,0,
        0,0,0,
        0,0,0,

        (float)white.r/256.0f , (float)white.g/256.0f, (float)white.b/256.0f,
        (float)white.r/256.0f , (float)white.g/256.0f, (float)white.b/256.0f,
        (float)white.r/256.0f , (float)white.g/256.0f, (float)white.b/256.0f,
        

    };

    this->object = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data, g_color_buffer_data, GL_FILL);    
}




bounding_box_t Ball::get_bbox() {
    return this->bbox;;
}

void Ball::update_bbox(){
    this->bbox.x = this->position.x;
    this->bbox.y = this->position.y;
}

void Ball::tick() {
    this->position.x -= this->xspeed;
    this->position.y -= this->yspeed;
    if(this->position.y > 20){
        // cout<<"above"<<endl;
        this->yspeed = 0;
        this->position.y = 20;
    }
    if(this->position.y < -12){
        // cout<<"below"<<endl;
        this->yspeed = 0;
        this->position.y = -12;   
    }
    this->update_bbox();
}

// void Ball::yforce(float a) {
//     // if(a>0 && this->yspeed < YLIM){ 
//     if(a>0){
//         this->yspeed += a;
//     }
//     if(a <0 &&  this->yspeed > -YLIM ){
//         this->yspeed += a;
//     }
//     // cout<<this->yspeed<<endl;
//     this->position.y -= this->yspeed;
//     // cout<<this->position.y<<endl;
//     if(this->position.y > 20){
//         // cout<<"above"<<endl;
//         this->yspeed = 0;
//         this->position.y = 20;
//     }
//     if(this->position.y < -15){
//         // cout<<"below"<<endl;
//         this->yspeed = 0;
//         this->position.y = -15;   
//     }
//     this->update_bbox();
// }

void Ball::yforce(float a) {
    this->yspeed += a;
}

void Ball::xforce(float a) {
    this->xspeed += a;
}

void Ball::resetForce() {
    this->yspeed = 0;
    this->xspeed = 0;
}



