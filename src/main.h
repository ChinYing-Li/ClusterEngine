#pragma once

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include "includes/gl_headers.h"

#include "color.h"

// ---- Logic ----

enum direction_t { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };

enum carCamera
{
    frontview = 1,
    rearview = 2
};

enum camMove
{
    move_forward  = 3,
    move_backward = 4,
    turn_cw       = 5,
    turn_ccw      = 6
};

// turn this into class AABB; axis aligned in world space
struct bounding_box_t {
    float x;
    float y;
    float width;
    float height;
};

// nonedit.cpp
GLFWwindow *initGLFW(int width, int height);
GLuint     LoadShaders(const char *vertex_file_path, const char *fragment_file_path);

//void       draw3DObject(VAO* vao);

// input.cpp
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void keyboardChar(GLFWwindow *window, unsigned int key);
//void mouseButton(GLFWwindow *window, int button, int action, int mods);

// other_handlers.cpp
void error_callback(int error, const char *description);
void quit(GLFWwindow *window);
void reshapeWindow(GLFWwindow *window, int width, int height);

extern float screen_zoom, screen_center_x, screen_center_y;
void reset_screen();
void scroll_call(double x_scroll, double y_scroll);




