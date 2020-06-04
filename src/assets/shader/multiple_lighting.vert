#version 330 core
layout (location = 0) in vec3 vposition;
layout (location = 1) in vec3 vnormal;
layout (location = 2) in vec2 vtexcoord;

out vec3 pos;
out vec3 normal;
out vec2 texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 project;

void main()
{
    pos = vec3(model * vec4(vposition, 1.0));
    texcoord = vtexcoord;
    normal = normalize(mat3(transpose(inverse(model))) * normalize(vnormal));
    gl_Position = project * view * vec4(pos, 1.0);
}
