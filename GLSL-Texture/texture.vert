#version 120

attribute vec2 position;
attribute vec2 texCoord;

varying vec2 tc;

void main()
{
   tc = texCoord;
   gl_Position = gl_ModelViewProjectionMatrix * vec4(position, 0.0, 1.0);
}