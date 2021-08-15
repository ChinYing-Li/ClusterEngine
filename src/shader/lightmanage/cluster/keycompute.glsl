#version 440

uniform vec2 u_tile_size;
uniform sampler2D u_depth_tex;
uniform float u_k_inv;
uniform float u_z_near;

void main() {
    ivec2 screen_pos = ivec2(gl_GlobalInvocationID.xy);
    vec2 screen_pos_normalized = screen_pos / 
}
