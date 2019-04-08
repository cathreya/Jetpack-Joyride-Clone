#include "firelines.h"
#include "main.h"
#include <iostream>
using namespace std;

FireLine::FireLine( float x, float y, color_t color){
    this->position = glm::vec3(x, y, 0);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    float x2 = uniform_int_distribution<long long>(-6, 6)(rng);
    if(x2 == 0) x2++;
    x2 += x;
    
    float y2 = uniform_int_distribution<long long>(2, 4)(rng);
    y2-= y;

    // cout<<x<<" "<<y<<" "<<x2<<" "<<y2<<endl;
    int t = 0;

    if(abs(x-x2) > abs(y-y2)){
        for(float i=min(x,x2);i<max(x,x2);i+=0.8){
            t++;
            if(t%2==0){
                this->fp.pb(FireParticle(i,twoPointForm(x,y,x2,y2,i),COLOR_RED));
            }
            else{
                this->fp.pb(FireParticle(i,twoPointForm(x,y,x2,y2,i),COLOR_ORANGE));
            }
        }
    }
    else{
        for(float i=min(y,y2);i<max(y,y2);i+=0.8){
            t++;
            if(t%2==0){
                this->fp.pb(FireParticle(twoPointForm2(x,y,x2,y2,i),i,COLOR_RED));
            }
            else{
                this->fp.pb(FireParticle(twoPointForm2(x,y,x2,y2,i),i,COLOR_ORANGE));
            }
        }   
    }

    this->x2 = x2;
    this->y2 = y2;
}

void FireLine::draw(glm::mat4 VP) {
    for(auto &i: this->fp){
        i.draw(VP);
    }
}

void FireLine::move(float plus) {
    this->position.x -= plus;
    for(auto &i: this->fp){
        i.move(plus);
    }   
}
