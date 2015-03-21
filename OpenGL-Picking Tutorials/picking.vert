#version 120

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

varying vec4 color;

attribute vec4 position;
attribute vec3 normal;
uniform vec4 diffuse;
vec4 ambient = vec4;
vec4 specular = vec4;
vec4 shininess = vec4;
vec4 lightDir = vec4();

void main()
{
   mat4 mvp_matrix = proj_matrix * view_matrix * model_matrix;
   mat4 mv_matrix = view_matrix * model_matrix;
   Normal = normalize(model_matrix * normal);
   eye = -(mv_matrix * position);
   
	// set the specular term to black
	vec4 spec = vec4(0.0);

	// normalize both input vectors
	vec3 n = normalize(Normal);
	vec3 e = normalize(vec3(eye));

	float intensity = max(dot(n, lightDir), 0.0);

	// if the vertex is lit compute the specular color
	if (intensity > 0.0) {
		// compute the half vector
		vec3 h = normalize(l_dir + e);	
		// compute the specular term into spec
		float intSpec = max(dot(h,n), 0.0);
		spec = specular * pow(intSpec,shininess);
	}
   color = max(intensity * diffuse + spec, ambient);
   gl_Position = mvp_matrix * position;
}