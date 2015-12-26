#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ogl/shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Shader glslShader("glsl test");
GLuint program, vertex_loc, mvp_matrix_loc;

static const GLfloat VertexData[] = 
{
	0.0f,  0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};

void init_shader()
{
	glslShader.init();
	glslShader.attach(GL_VERTEX_SHADER, "glsl.vert");
	glslShader.attach(GL_FRAGMENT_SHADER, "glsl.frag");
	glslShader.link();
	glslShader.use();
	program = glslShader.GetProgram();
	mvp_matrix_loc = glGetUniformLocation(program, "mvp_matrix");
	vertex_loc = glGetAttribLocation(program, "position");
	glEnableVertexAttribArray(vertex_loc);
	glVertexAttribPointer(vertex_loc, 3, GL_FLOAT, GL_FALSE, 0, VertexData);

}

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	init_shader();
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(720, 640);
	glutCreateWindow("glsl-TEST");
	GLenum status = glewInit();
	if (status != GLEW_OK)
		std::cerr << glewGetErrorString(status) << std::endl;
	init();
	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}