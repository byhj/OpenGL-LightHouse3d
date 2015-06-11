#version 120

uniform int code;

void main()
{
   gl_FragColor = vec4(code / 255.0, 0.0, 0.0, 0.0);
}
