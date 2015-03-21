#version 120

varying vec4 color;
vec4 ambient = vec4(1.0, 1.0, 1.0, 1.0);
vec4 lightPos = vec4(3, 1.5 , 5 ,0);
vec4 material = vec4(0.8, 0.8, 0.5, 0.0);

void main()
{
   vec3 normal;
   vec4 diffuse = vec4(1.0, 1.0, 1.0, 1.0);
   normal = normalize(gl_NormalMatrix * gl_Normal);
   vec3 lightDir = normalize(vec3(lightPos));
   float dotLight = max(dot(normal, lightDir), 0.0);
   color = dotLight * diffuse * material + ambient * 0.8;
   gl_Position = ftransform();
}