#version 330 core
layout (location = 0) in vec3 i_position;
layout (location = 1) in vec3 i_normal;
layout (location = 2) in vec2 i_texcoords;

out vec3 o_position;
out vec3 o_normal;
out vec2 o_texcoords;
out vec3 o_world_position;

uniform mat4 u_model_mat;
uniform mat4 u_view_mat;
uniform mat4 u_project_mat;
uniform mat4 u_MVP;

void main()
{
    o_position = i_position;
    o_normal = i_normal;
    o_texcoords = i_texcoords;

    gl_Position = u_MVP * vec4(i_position, 1.0);
}
