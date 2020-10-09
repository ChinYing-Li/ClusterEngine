#version 330 core

int indices[6] = int[](0, 1, 2, 2, 1, 3);

out vec3 position;
out vec2 tex_coords;

vec3 vert[4] = vec3[](vec3(-1, -1, 0), vec3(1, -1, 0), vec3(-1, 1, 0), vec3(1, 1, 0));

vec2 tex_coords[4] = vec2[]
        (vec2(0, 0), vec2(1, 0), vec2(0, 1),vec2(1, 1));

void main()
{
    int index = indices[gl_VertexID];
    position = vert[index];
    tex_coords = tex_coords[index];
    gl_Position = vec4(vert[index], 1);
}
