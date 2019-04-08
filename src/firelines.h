#define GLM_ENABLE_EXPERIMENTAL
#include "main.h"
#include "fireparticle.h"
#include <vector>
using namespace std;

#ifndef FIREL_H
#define FIREL_H


class FireLine {
public:
    FireLine() {}
    FireLine(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void move(float );
    vector<FireParticle> fp;

    float x2,y2;
    
    

private:

};



#endif 
