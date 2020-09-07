#version 330 core

in vec3 position;

out vec3 o_position;

uniform mat4 project_transform;
uniform mat4 view_transform;
uniform mat4 model_transform;

void main()
{
    mat4 MVP_transform = project_transform * view_transform * model_transform;
    o_position = position;
    vec4 pos = MVP_transform * vec4(position, 1.0);
    gl_Position = pos.xyww;
}

