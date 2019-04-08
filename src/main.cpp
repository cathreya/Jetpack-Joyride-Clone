#include "main.h"
#include "timer.h"
#include "ball.h"
#include "platform.h"
#include "wall.h"
#include "coin.h"
#include "firelines.h"
#include "firebeam.h"
#include "boomerang.h"
#include "magnet.h"
#include "slow.h"
#include "sword.h"
#include "shield.h"
#include "projectile.h"
#include "propulsion.h"
#include "ring.h"
#include "segment.h"
#include "dragon.h"
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
std::map<GLchar, Character> Characters;
Ball ball1;
Ball ball2;
Platform plat;
vector<Wall> wall;
vector<FireLine> flines;



FireBeam *fireb = 0;
Boomerang *boom = 0;
Slow *slow = 0;
Shield *shield = 0;

string status="Normal";

int lives = 10;
vector<Segment> display;
vector<Segment> display2;

Magnet *mag = 0;
Ring *ring = 0;
Dragon* dragon = 0;
Sword* sword = 0;

int ringed = 0;
int isdragon = 0;
int immune = 0;
int pulled = 0;
int score = 0;
int swordout = 0;

float baseSceneSpeed = 0.3;
float sceneSpeed = 0.3;
vector<Projectile> proj;
vector<Projectile> iceballs;
vector<Propulsion> prop;


vector<Coin> coins;

float screen_zoom = 0.2, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);
int skip = 0;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

float twoPointForm(float x1, float y1, float x2, float y2, float x){
    float m = (y2-y1)/(x2-x1);

    float y = m*(x-x1) + y1;
    return y;
}

float twoPointForm2(float x1, float y1, float x2, float y2, float y){
    float m = (x2-x1)/(y2-y1);

    float x = m*(y-y1) + x1;
    return x;
}

// void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
// {
//     // Activate corresponding render state  
    
//     glUniform3f(glGetUniformLocation(programID, "textColor"), color.x, color.y, color.z);
//     glActiveTexture(GL_TEXTURE0);
//     // glBindVertexArray(VAO);
//     glBindVertexArray(0);

//     // Iterate through all characters
//     std::string::const_iterator c;
//     for (c = text.begin(); c != text.end(); c++) 
//     {
//         Character ch = Characters[*c];

//         GLfloat xpos = x + ch.Bearing.x * scale;
//         GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

//         GLfloat w = ch.Size.x * scale;
//         GLfloat h = ch.Size.y * scale;
//         // Update VBO for each character
//         GLfloat vertices[6][4] = {
//             { xpos,     ypos + h,   0.0, 0.0 },            
//             { xpos,     ypos,       0.0, 1.0 },
//             { xpos + w, ypos,       1.0, 1.0 },

//             { xpos,     ypos + h,   0.0, 0.0 },
//             { xpos + w, ypos,       1.0, 1.0 },
//             { xpos + w, ypos + h,   1.0, 0.0 }           
//         };
//         // Render glyph texture over quad
//         glBindTexture(GL_TEXTURE_2D, ch.TextureID);
//         // Update content of VBO memory
//         // glBindBuffer(GL_ARRAY_BUFFER, VBO);
//         glBindBuffer(GL_ARRAY_BUFFER, 0);
//         glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

//         glBindBuffer(GL_ARRAY_BUFFER, 0);
//         // Render quad
//         glDrawArrays(GL_TRIANGLES, 0, 6);
//         // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
//         x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
//     }
//     glBindVertexArray(0);
//     glBindTexture(GL_TEXTURE_2D, 0);
// }


/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!

    
    glm::vec3 target (ball1.position.x, ball1.position.y, 0);
        
    
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (1, 0, 0);
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // if(screen_zoom > 0.3){
    //     Matrices.view = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(ball1.position.x, ball1.position.y, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane
    // }
    // else{
        Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane
    // }

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
    // ball2.draw(VP);
    plat.draw(VP);

    if(slow){
        slow->draw(VP);
    }

    for(auto p:proj){
        p.draw(VP);
    }

    if(shield){
        shield->draw(VP);
    }
    if(fireb){
        fireb->draw(VP);
    }
    if(boom){
        boom->draw(VP);
    }
    if(mag){
        mag->draw(VP);
    }
    if(ring){
        ring->draw(VP);
    }
    if(dragon){
        dragon->draw(VP);
    }
    if(sword){
        sword->draw(VP);
    }

    for(auto &w : iceballs){
        w.draw(VP);
    }

    for(auto &w : wall){
        w.draw(VP);
    }
    for(auto &w : coins){
        w.draw(VP);
    }
    for(auto &w : flines){
        w.draw(VP);
    }

    for(auto &seg : display){
        seg.draw(VP);
    }
    for(auto &seg : display2){
        seg.draw(VP);
    }

    for(auto &p : prop){
        p.draw(VP);
    }

}

void display_score(){
    string s = to_string(score);
    float x = 18;
    float y = 18;
    reverse(s.begin(), s.end());
    display.clear();
    for(char c: s){
        display.pb(Segment(c, x, y));
        x-= 2.5;
    }
    x = -15;
    y = 18;
    s = to_string(lives);
    reverse(s.begin(), s.end());
    display2.clear();
    for(char c: s){
        display2.pb(Segment(c,x,y));
        x -= 2.5;
    }
}

void move_wall(){

    vector<int> er;
    vector<Wall> pu;

    for(int i=0;i<wall.size();i++){
        auto &w = wall[i];
        w.position.x -= sceneSpeed;
        if(w.position.x < -30){
            er.pb(i);
        }
        if(w.position.x <= 0 && w.position.x >-sceneSpeed){
            pu.pb(Wall(COLOR_BLACK));
        }
    }
    for(auto i:er){
        wall.erase(wall.begin()+i);
    }
    for(auto i:pu){
        wall.pb(i);
    }
}

void move_coin(){
    vector<int> er;
    vector<Coin> pu;

    vector<color_t> colors = {COLOR_GOLD, COLOR_DARKORANGE, COLOR_BROWN};

    int r = uniform_int_distribution<long long>(1,10)(rng);
    int val = uniform_int_distribution<long long>(0, 2)(rng);
    if(r == 1){
        int x = 20;
        int y = uniform_int_distribution<long long>(-15, 15)(rng);
        
        pu.pb(Coin(val+1, x,y, colors[val]));

    }


    for(int i=0;i<coins.size();i++){
        auto &w = coins[i];
        w.move(sceneSpeed);
        if(w.position.x < -30){
            er.pb(i);
        }
    }
    for(auto i:er){
        coins.erase(coins.begin()+i);
    }
    for(auto i:pu){
        coins.pb(i);
    }   
}   

void move_fl(){
    vector<int> er;
    vector<FireLine> pu;

    if(uniform_int_distribution<long long>(0, 50)(rng) == 1){
        int x = 50;
        int y = uniform_int_distribution<long long>(-15, 15)(rng);
        
        pu.pb(FireLine(x,y, COLOR_RED));

    }

    for(int i=0;i<flines.size();i++){
        auto &w = flines[i];
        w.move(sceneSpeed);
        if(w.position.x < -25){
            er.pb(i);
        }
    }
    for(auto i:er){
        flines.erase(flines.begin()+i);
    }
    for(auto i:pu){
        flines.pb(i);
    }

    if(!fireb){
        if(uniform_int_distribution<> (0,300)(rng) == 1){
            if(uniform_int_distribution<>(0,1)(rng) == 1){
                fireb = new FireBeam(-sceneSpeed, 0, -20, COLOR_MAROON);
            }
            else{
                fireb = new FireBeam(sceneSpeed, 0, 20, COLOR_MAROON);
            }
        }
    }

    if(!boom){
        if(uniform_int_distribution<> (0,300)(rng) == 1){
            if(uniform_int_distribution<>(0,1)(rng) == 1){
                boom = new Boomerang(20,10, -sceneSpeed, -0.07, COLOR_MAROON);   
            }
            else{
                boom = new Boomerang(20,-10, -sceneSpeed, 0.07, COLOR_MAROON);
            }
        }   
    }
    else{
        boom->move(sceneSpeed);
    }

    if(!mag){
        if(uniform_int_distribution<> (0,800)(rng) == 1){
            float x = uniform_real_distribution<>(-10,10)(rng);
            float y = uniform_real_distribution<>(-10,10)(rng);
            float force = uniform_real_distribution<>(0.001,0.003)(rng);

            mag = new Magnet(force,x,y , &ball1.position.x, &ball1.position.y, COLOR_BRIGHT_RED);
            ball1.yspeed = ball1.xspeed = 0;
            pulled = 1;
        }
    }
    else{
        // mag->move(sceneSpeed);
    }

    if(!ring){
        if(uniform_int_distribution<> (0,80)(rng) == 1){
            float y = uniform_real_distribution<>(-10,10)(rng);
            ring = new Ring(30,y,COLOR_BLUE);
        }
    }
    else{
        ring->move(sceneSpeed);
        if(ring->position.x < -30){
            delete ring;
            ring = 0;
        }
    }

    if(!dragon){
        if(uniform_int_distribution<> (0,1000)(rng) == 1){
            dragon = new Dragon(18.5,&ball1.position.y,COLOR_DARK_BLUE);
            isdragon = 1;
        }
    }
}   

void make_slow(){
    if(!slow){
        int spawn = uniform_int_distribution<>(1,2000)(rng);
        if(spawn == 1){
            float xvel = uniform_real_distribution<>(0.02,0.1)(rng);
            float yvel = uniform_real_distribution<>(0.1,0.33)(rng);
            slow = new Slow(20,-10,xvel,-yvel, COLOR_ORANGE);            
        }
    }

    if(slow){
        slow->move(sceneSpeed);
    }

    if(slow && slow->position.x < -20){
        delete slow;
        slow = 0;
    }
    
    if(!shield){
        int spawn = uniform_int_distribution<>(1,2000)(rng);
        if(spawn == 1){
            float xvel = uniform_real_distribution<>(0.02,0.1)(rng);
            float yvel = uniform_real_distribution<>(0.1,0.33)(rng);
            shield = new Shield(20,-10,xvel,-yvel, COLOR_GREEN);
        }
    }

    if(shield){
        shield->move(sceneSpeed);
    }

    if(shield && shield->position.x < -20){
        delete shield;
        shield = 0;
    }

    if(!sword){
        int spawn = uniform_int_distribution<>(1,1000)(rng);
        if(spawn == 1){
            float y = uniform_real_distribution<>(-16,15)(rng);
            sword = new Sword(20,y, &ball1.position.x, &ball1.position.y, COLOR_GREEN);
        }
    }
    else{
        sword->move(sceneSpeed);
        if(sword->position.x < -30){
            delete sword;
            sword = 0;
        }
    }

}


void move_scene(){
    move_wall();
    move_coin();
    move_fl();
    make_slow();
}

void scroll_callback(GLFWwindow *window, double x, double y){
    screen_zoom += 0.01*y;
    if(screen_zoom < 0.2) screen_zoom = 0.2;
    if(screen_zoom > 0.8) screen_zoom = 0.8;
    // cout<<sceneSpeed<<endl;
    reset_screen();
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
       double xpos, ypos;
       //getting cursor position
       glfwGetCursorPos(window, &xpos, &ypos);

       GLdouble axpos,aypos,azpos;
       GLint viewport[4];
        GLdouble modelview[16];
        GLdouble projection[16];

       glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
       glGetDoublev( GL_PROJECTION_MATRIX, projection );
       glGetIntegerv( GL_VIEWPORT, viewport );

       gluUnProject(xpos,ypos,0, modelview, projection, viewport, &axpos, &aypos, &azpos);
        
        axpos *= 20;
        aypos *= -20;

       // cout<<axpos<<" "<<aypos<<endl;

       float ang = atan2(aypos-ball1.position.y, axpos-ball1.position.x);
       // cout<<ang*180/M_PI<<endl;
       float xvel = 0.3*cos(ang);
       float yvel = 0.3*sin(ang);

       
        proj.pb(Projectile(ball1.position.x,ball1.position.y+0.2,-xvel,-yvel, COLOR_BLUE));


    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    if (left) {
        if(!ringed){
            ball1.move(sceneSpeed);
        }
        else{
            int cur = ring->cur;
            if( cur > 0){
                cur--;
                ring->cur--;
                ball1.set_position(ring->pathx[cur], ring->pathy[cur]);
            }
            else{
                ringed = 0;
            }
        }
    }
    if (right) {
        if(!ringed){
            int pan = ball1.move(-sceneSpeed);
            if(pan) move_scene();
            
        }
        else{
            int cur = ring->cur;
            if( cur+1 < ring->pathx.size()){
                cur++;
                ring->cur++;
                int pan = ball1.set_position(ring->pathx[cur], ring->pathy[cur]);
                if(pan) {
                    move_scene();
                    ring->cur --;
                    cur--;
                }
            }
            else{
                ringed = 0;
                ring->cur = 0;
                immune = 0;
                ball1.reset();

            }
        }
    }
    if (!ringed && up) {
        ball1.yforce(-YACC);
        float x = uniform_real_distribution<>(ball1.position.x-ball1.get_bbox().width/2,ball1.position.x)(rng);
        prop.pb(Propulsion(x , ball1.position.y-1.3, COLOR_RED));
    }
    if(!ringed && down){
        ball1.yforce(YACC);
    }

    double xpos, ypos;
    
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);




}

void dead(){
    cout<<"LOST A LIFE"<<endl;
    lives -= 1;
    if(lives == 0){
        cout<<"GAME OVER"<<endl;
        cout<<"SCORE : "<<score<<endl;
        quit(window);
    }
    score -= uniform_int_distribution<long long> (1,10)(rng);
    if(score < 0) score =0;
    ball1.yforce(500*G);
    immune = 1;
}

    
void tick_elements() {
    vector<int> er;
    int i = 0;
    if(dragon){
       if(uniform_int_distribution<> (0,30)(rng) == 1){
            iceballs.pb(Projectile(dragon->position.x-3, dragon->position.y+5,0.5,0, COLOR_ORANGE));
        }
        if(swordout && detect_collision(dragon->get_bbox(),sword->get_bbox())){
            isdragon += 1;
        } 
    }

    er.clear();
    i =0;
    for(auto &p : prop){
        p.tick();
        p.yforce(G);
        if(p.position.y <= -15){
            er.pb(i);
        }
        i++;
    }
    for(int j:er){
        prop.erase(prop.begin()+j);
    }

    if(ring && detect_collision(ball1.get_bbox(), ring->get_bbox())){
        ringed = 1;
        ball1.set_yspeed(0);
        ball1.set_xspeed(0);
    }

    if(!ringed){
        ball1.tick();
        ball1.yforce(G);
    }
    else{
        immune = 1;
    }
    if(immune){
        ball1.shield();
    }
    if(boom){
        boom->tick();
        boom->xforce(G);
        if(swordout && detect_collision(boom->get_bbox(),sword->get_bbox())){
            boom->position.x = 31;
        }
        if(boom->position.x > 30){
            delete boom;
            boom = 0;
        }
    }
    if(mag){
        if(swordout && detect_collision(mag->get_bbox(),sword->get_bbox())){
            pulled = 500;
        }

        if(detect_collision(mag->get_bbox(), ball1.get_bbox())){
            ball1.xspeed = ball1.yspeed = 0;
        }
        else{
            float angle = atan2((ball1.position.y - mag->position.y),(ball1.position.x - mag->position.x));
            ball1.yforce(mag->force*sin(angle)-G);
            ball1.xforce(mag->force*cos(angle));
        }

    }

    if(sword && !swordout){
        if(detect_collision(sword->get_bbox(),ball1.get_bbox())){
            sword->flag=0;
            immune = 1;
            swordout = 1;
        }
    }

    if(slow){
        slow->tick();
        slow->yforce(G);
    }
    if(shield){
        shield->tick();
        shield->yforce(G);
    }

    if(fireb){
        int ret = fireb->tick();
        if(ret){
            delete fireb;
            fireb = 0;
        }

        if(fireb && swordout && detect_collision(fireb->get_bbox(),sword->get_bbox())){
            delete fireb;
            fireb = 0;
        }
    }
    for(auto &p : proj){
        p.tick();
        p.yforce(G);
    }

    er.clear();
    for(int i=0;i<coins.size();i++){
        auto &coin = coins[i];
        if(detect_collision(ball1.get_bbox(), coin.get_bbox())){
            er.pb(i);
            score += coin.value;
        }
    }
    for(int i:er){
        coins.erase(coins.begin()+i);
    }
    er.clear();
    for(int i=0;i<proj.size();i++){
        auto &p = proj[i];
        if(p.position.y == -15){
            er.pb(i);
        }
    }
    for(int i:er){
        proj.erase(proj.begin()+i);
    }


    for(auto &fp: flines){
        vector<int> er;
        int i=0;
        for(auto &fp2: fp.fp){
            if(!immune && detect_collision(ball1.get_bbox(), fp2.get_bbox())){
                dead();
            }
            if(swordout && detect_collision(fp2.get_bbox(),sword->get_bbox())){
                er.pb(i);
            }
            for(auto &p : proj){
                if(detect_collision(p.get_bbox(), fp2.get_bbox())){
                    er.pb(i);    
                }
            }
            i++;
        }
        sort(er.begin(), er.end());
        er.erase(unique(er.begin(), er.end()),er.end());
        for(int j:er){
            fp.fp.erase(fp.fp.begin()+j);
        }
    }

    if(slow){
        if(detect_collision(ball1.get_bbox(), slow->get_bbox())){
            delete slow;
            slow = 0;
            skip = 1;
            sceneSpeed *= 0.5;
            if(fireb){
                fireb->yspeed *= 0.5;
            }
        }
    }
    
    if(shield){
        if(detect_collision(ball1.get_bbox(), shield->get_bbox())){
            delete shield;
            shield = 0;
            immune = 1; 
        }
    }


    if(fireb){
        if(!immune && detect_collision(ball1.get_bbox(),fireb->get_bbox())){
            dead();
        }
    }

    if(boom){
        if(!immune && detect_collision(ball1.get_bbox(), boom->get_bbox())){
            dead();
        }
    }

    er.clear();
    i = 0;
    for(auto &w:iceballs){
        w.tick();
        w.yforce(G);
        if(!immune && detect_collision(ball1.get_bbox(), w.get_bbox())){
            dead();
        }
        if(w.position.y == -15 || swordout && detect_collision(w.get_bbox(),sword->get_bbox())){
            er.pb(i);
        }
        i++;
    }
    for(int i:er){
        iceballs.erase(iceballs.begin()+i);
    }

    // int w = glutBitmapLength(GLUT_BITMAP_8_BY_13, to_string(score));
    // string s = to_string(score);
    // drawBitmapText(s,10,10);
    
    
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1 = Ball(-3, 0, 0,0, COLOR_RED);    
    // ball2 = Ball(3,0, 0.05, 0, COLOR_GREEN);
    plat = Platform(COLOR_BLACK);
    wall.pb(Wall(COLOR_BLACK));

    
    
        
    // for(int i=0;i<250;i++) move_scene();


    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");



    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

    //FREETYPE STUFF

    // FT_Library ft;
    // if (FT_Init_FreeType(&ft))
    //     std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    // FT_Face face;
    // if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
    //     std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;  

    // // FT_Set_Pixel_Sizes(face, 0, 48);  
    // FT_Set_Pixel_Sizes(face, 64, 0);  
    // // Disable byte-alignment restriction
    // glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 

    // // Load first 128 characters of ASCII set
    // for (GLubyte c = 0; c < 128; c++)
    // {
    //     // Load character glyph 
    //     int err;
    //     if (err = FT_Load_Char(face, c, FT_LOAD_RENDER))
    //     {
    //         std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
    //         cout<<err<<endl;
    //         continue;
    //     }
    //     // Generate texture
    //     GLuint texture;
    //     glGenTextures(1, &texture);
    //     glBindTexture(GL_TEXTURE_2D, texture);
    //     glTexImage2D(
    //         GL_TEXTURE_2D,
    //         0,
    //         GL_RED,
    //         face->glyph->bitmap.width,
    //         face->glyph->bitmap.rows,
    //         0,
    //         GL_RED,
    //         GL_UNSIGNED_BYTE,
    //         face->glyph->bitmap.buffer
    //     );
    //     // Set texture options
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //     // Now store character for later use
    //     Character character = {
    //         texture,
    //         glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
    //         glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
    //         face->glyph->advance.x
    //     };
    //     Characters.insert(std::pair<GLchar, Character>(c, character));
    // }
    // glBindTexture(GL_TEXTURE_2D, 0);
    // // Destroy FreeType once we're finished
    // FT_Done_Face(face);
    // FT_Done_FreeType(ft);
    // RenderText("This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, sceneSpeedf));

}

int countdown(int &var, int dur){
    if(var == 0) return 0;
    var ++;
    if(var >= dur){
        var = 0;
        return 1;
    }
    return 0;
}


int main(int argc, char **argv) {
    
    int width  = WIDTH;
    int height = HEIGHT;

    
    window = initGLFW(width, height);

    initGL (window, width, height);


    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            string tmp = "Score: ";
            tmp += to_string(score);
            tmp += " Lives: ";
            tmp += to_string(lives);
            tmp += " Status: ";
            bool t = 0;
            if(ringed){
                t = 1;
                tmp += "Inside Shelter Ring ";
            }
            if(immune){
                t = 1;
                tmp += "Shielded ";
            }
            if(swordout){
                t = 1;
                tmp += "Sword! ";
            }
            if(pulled){
                t = 1;
                tmp += "Attracted towards a Magnet ";
            }
            if(skip){
                t=  1;
                tmp += "Time Slowed Down ";
            }
            if(!t) tmp += "Normal";

            glfwSetWindowTitle(window, tmp.c_str());
            // cout<<wall.size()<<" "<<flines.size()<<" "<<proj.size()<<" "<<iceballs.size()<<endl;
            // cout<<prop.size()<<endl;
            display_score();    
            if(countdown(skip, 500)){
                sceneSpeed = baseSceneSpeed;
                
                if(fireb){
                    float a = fireb->yspeed;
                    fireb->yspeed = baseSceneSpeed;
                    if(a < 0){
                        fireb->yspeed *= -1;
                    }
                }
            }   
            if(countdown(immune, 500)){
                
                ball1.reset();
            }
            if(countdown(swordout,500)){
                
                delete sword;
                sword = 0;
            }
            if(countdown(pulled, 300)){
                
                delete mag;
                mag = 0;
                ball1.resetForce();
            }
            if(countdown(isdragon, 300)){
                delete dragon;
                dragon = 0;
            }

            
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    // cout<<a.x<<" "<<b.x<<endl;
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));

    // return ()
}

void reset_screen() {

    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;

    // float top    = ball1.position.y + 4 / screen_zoom;
    // float bottom = ball1.position.y - 4 / screen_zoom;
    // float left   = ball1.position.x - 4 / screen_zoom;
    // float right  = ball1.position.x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
