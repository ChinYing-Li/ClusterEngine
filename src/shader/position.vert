#version 330 core
layout (location = 0) in vec3 i_position;
layout (location = 1) in vec3 i_normal;
layout (location = 2) in vec2 i_texcoords;

out vec3 position;
out vec3 normal;
out vec2 texcoords;
out vec3 world_position;

uniform mat4 model_transform;
uniform mat4 view_transform;
uniform mat4 project_transform;

void main()
{
    position = i_position;
    normal = i_normal;
    texcoords = i_texcoords;

    gl_Position = project * view * model * vec4(i_position, 1.0);
}
