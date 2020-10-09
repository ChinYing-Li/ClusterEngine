#pragma once

#include "glincludes.h"

struct glsl_type_set {
  GLenum      type;
  const char* name;
};

void glsl_print_uniforms(unsigned int program);
void gl_debug();
