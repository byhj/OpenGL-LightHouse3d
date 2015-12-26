#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ogl/shader.h>

Shader textureShader("toon Shading");
GLuint program, vertex_loc, tc_loc;
GLuint ibo, tex_loc, texture;
#include <IL/il.h>

GLuint loadTexture(const  char* theFileName)
{
	ILuint imageID;				// Create an image ID as a ULuint
	GLuint textureID = 0;			// Create a texture ID as a GLuint
	ILboolean success;			// Create a flag to keep track of success/failure
//	ILenum error;				// Create a flag to keep track of the IL error state
	ilInit();
	ilGenImages(1, &imageID); 		// Generate the image ID
	ilBindImage(imageID); 			// Bind the image
	success = ilLoadImage(theFileName); 	// Load the image file
	
	if (success) {
	   success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
		glGenTextures(1, &textureID);
		// Bind the texture to a name
		glBindTexture(GL_TEXTURE_2D, textureID);

		// Set texture clamping method
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		// Set texture interpolation method to use linear interpolation (no MIPMAPS)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		// Specify the texture specification
		glTexImage2D(GL_TEXTURE_2D, 				// Type of texture
			0,				// Pyramid level (for mip-mapping) - 0 is the top level
			ilGetInteger(IL_IMAGE_FORMAT),	// Internal pixel format to use. Can be a generic type like GL_RGB or GL_RGBA, or a sized type
			ilGetInteger(IL_IMAGE_WIDTH),	// Image width
			ilGetInteger(IL_IMAGE_HEIGHT),	// Image height
			0,				// Border width in pixels (can either be 1 or 0)
			ilGetInteger(IL_IMAGE_FORMAT),	// Format of image pixel data
			GL_UNSIGNED_BYTE,		// Image data type
			ilGetData());			// The actual image data itself
	}


	ilDeleteImages(1, &imageID); // Because we have already copied image data into texture data we can release memory used by image.
	std::cout << "Texture creation successful." << std::endl;
	return textureID; // Return the GLuint to the texture so you can use it!
}
static const float VertexData[] =
{
	0.8, 0.8,
	-0.8, 0.8,
	-0.8, -0.8,
	0.8, -0.8
};

static const float TexCoordData[] = {
	1.0, 0.0,
	1.0, 1.0, 
	0.0, 1.0,
	0.0, 0.0
};

static const GLushort ElememtData[] = {
	0, 1, 3,
	1, 2, 3
};

void init_shader()
{
	textureShader.init();
	textureShader.attach(GL_VERTEX_SHADER, "texture.vert");
	textureShader.attach(GL_FRAGMENT_SHADER, "texture.frag");
	textureShader.link();
	textureShader.use();
	program = textureShader.GetProgram();
	tex_loc = glGetUniformLocation(program, "tex");
	glUniform1i(tex_loc, 0);
	vertex_loc = glGetAttribLocation(program, "position");
	tc_loc = glGetAttribLocation(program, "texCoord");
	glEnableVertexAttribArray(vertex_loc);
	glEnableVertexAttribArray(tc_loc);
	glVertexAttribPointer(vertex_loc, 2, GL_FLOAT, GL_FALSE, 0, VertexData);
	glVertexAttribPointer(tc_loc, 2, GL_FLOAT, GL_FALSE, 0, TexCoordData);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ElememtData), ElememtData, GL_STATIC_DRAW);
}

void init_texture()
{
	texture = loadTexture("crate.jpg");
}

void init()
{
	init_shader();
	init_texture();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glutSwapBuffers();
}

int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(720, 640);
	glutCreateWindow("toon");
	glewInit();
	init();
	glutDisplayFunc(render);
	glutMainLoop();
}
