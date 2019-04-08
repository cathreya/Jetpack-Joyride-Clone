#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <map>
#include <string>

using namespace std;
#define pb push_back

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// #include <ft2build.h>
// #include FT_FREETYPE_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define WIDTH 800
#define HEIGHT 400
#define G 0.004
#define YACC 0.02
#define YLIM 0.3

struct color_t {
    int r;
    int g;
    int b;
};

// nonedit.cpp
GLFWwindow *initGLFW(int width, int height);
GLuint     LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t color, GLenum fill_mode = GL_FILL);
void       draw3DObject(struct VAO *vao);

// input.cpp
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void keyboardChar(GLFWwindow *window, unsigned int key);
void mouseButton(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// other_handlers.cpp
void error_callback(int error, const char *description);
void quit(GLFWwindow *window);
void reshapeWindow(GLFWwindow *window, int width, int height);

// Types
struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int    NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint    MatrixID;
};

extern GLMatrices Matrices;

// ---- Logic ----

enum direction_t { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };

struct bounding_box_t {
    float x;
    float y;
    float width;
    float height;
};

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// mt19937 rng();

bool detect_collision(bounding_box_t a, bounding_box_t b);

float twoPointForm(float x1, float y1, float x2, float y2, float x);
float twoPointForm2(float x1, float y1, float x2, float y2, float x);


extern float screen_zoom, screen_center_x, screen_center_y;
void reset_screen();

//Freetype stuff
struct Character {
    GLuint     TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    GLuint     Advance;    // Offset to advance to next glyph
};

int countdown(int &a, int b);

void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);



// ---- Colors ----
extern const color_t COLOR_RED;
extern const color_t COLOR_BRIGHT_RED;
extern const color_t COLOR_MAROON;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_ORANGE; 
extern const color_t COLOR_GOLD ;
extern const color_t COLOR_DARKORANGE ;
extern const color_t COLOR_BROWN ;
extern const color_t COLOR_BLUE;
extern const color_t COLOR_DARK_BLUE;
extern const color_t COLOR_ICE;
#endif
