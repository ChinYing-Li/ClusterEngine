#version 330 core
layout (location = 0) in vec3 vposition;
layout (location = 1) in vec3 vnormal;
layout (location = 2) in vec3 vcolor;

out vec3 pos;
out vec3 normal;
out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    pos = vec3(model * vec4(vposition, 1.0));
    color = vcolor;
    normal = mat3(transpose(inverse(model))) * vnormal;
    gl_Position = projection * view * vec4(pos, 1.0);
}
