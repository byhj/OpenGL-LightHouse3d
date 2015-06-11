#version 120

uniform float time;

void main()
{
    vec4 position = vec4(gl_Vertex);
	position.z = sin(5.0 * position.x + time * 0.01) * 0.25;
	gl_Position = gl_ModelViewProjectionMatrix * position;
}