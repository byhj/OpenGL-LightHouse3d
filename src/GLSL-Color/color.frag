#version 120

varying vec4 FrontColor;
varying vec4 BackColor;

void main()
{
   if (gl_FrontFacing)
      gl_FragColor = FrontColor;
   else
      gl_FragColor = BackColor;
    
}