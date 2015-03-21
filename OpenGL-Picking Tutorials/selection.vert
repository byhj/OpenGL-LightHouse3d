#version 120

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

mat4 mvp_matrix = proj_matrix * view_matrix * model_matrix;

attribute vec4 position;

void main()
{
   gl_Position = mvp_matrix * position;
}