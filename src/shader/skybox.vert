#version 330 core

in vec3 i_position;

out vec3 o_position;

uniform mat4 u_project_mat;
uniform mat4 u_view_mat;
uniform mat4 u_model_mat;

void main()
{
    mat4 MVP_transform = u_project_mat * u_view_mat * u_model_mat;
    o_position = i_position;
    vec4 pos = MVP_transform * vec4(i_position, 1.0);
    gl_Position = pos.xyww;
}

