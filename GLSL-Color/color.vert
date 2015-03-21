#version 120

attribute vec4 color;
varying vec4 FrontColor;
varying vec4 BackColor;

void main()
{
   FrontColor = color;
   BackColor = vec4(0.0, 1.0, 0.0, 1.0);
   gl_Position = ftransform();
}