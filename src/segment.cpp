#include "segment.h"
#include "main.h"

Segment::Segment(char c, float x, float y){

    static GLfloat g_vertex_buffer_data[500001];
    this->position = glm::vec3(x, y, 0);
    bool line[8];
    for (int i = 0; i < 7; i++) line[i] = false;
    switch (c) {
	    case '0':
	        line[0] = line[1] = line[2] = line[3] = line[4] = line[5] = true;
	        break;
	    case '1':
	        line[1] = line[2] = true;
	        break;
	    case '2':
	        line[0] = line[1] = line[6] = line[4] = line[3] = true;
	        break;
	    case '3':
	        line[0] = line[1] = line[6] = line[2] = line[3] = true;
	        break;
	    case '4':
	        line[5] = line[6] = line[1] = line[2] = true;
	        break;
	    case '5':
	        line[0] = line[5] = line[6] = line[2] = line[3] = true;
	        break;
	    case '6':
	        line[0] = line[5] = line[6] = line[2] = line[3] = line[4] = true;
	        break;
	    case '7':
	        line[0] = line[1] = line[2] = true;
	        break;
	    case '8':
	        line[0] = line[1] = line[6] = line[4] = line[3] = line[2] = line[5] = true;
	        break;
	    case '9':
	        line[0] = line[1] = line[6] = line[3] = line[2] = line[5] = true;
	        break;
	    case '-':
	        line[6] = true;
	}

	float pts[7][4] = {
		{-1,1, 1,1},
		{1,1, 1,0},
		{1,0, 1,-1},
		{1,-1, -1,-1},
		{-1,-1, -1,0},
		{-1,0, -1,1},
		{-1,0, 1,0}
	};


	int j = 0;
	for(int i=0;i<7;i++){
		if(!line[i]) continue;

		g_vertex_buffer_data[j++] = pts[i][0];
		g_vertex_buffer_data[j++] = pts[i][1];
		g_vertex_buffer_data[j++] = 0;

		g_vertex_buffer_data[j++] = pts[i][2];
		g_vertex_buffer_data[j++] = pts[i][3];
		g_vertex_buffer_data[j++] = 0;
	}

	this->object = create3DObject(GL_LINES, j/3, g_vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Segment::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
