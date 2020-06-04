#pragma once

struct glsl_type_set {
  GLenum      type;
  const char* name;
};

void eTB_GLSL_print_uniforms (unsigned int program);
