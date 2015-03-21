#include <GL/glew.h>
#include <GL/freeglut.h>
#include <shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Shader uniformShader("glsl test");
GLuint program, vertex_loc, mvp_matrix_loc;
GLuint color_loc;

static const GLfloat VertexData[] = 
{
	0.0f,  0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};

void init_shader()
{
	uniformShader.init();
	uniformShader.attach(GL_VERTEX_SHADER, "Uniform.vert");
	uniformShader.attach(GL_FRAGMENT_SHADER, "Uniform.frag");
	uniformShader.link();
	uniformShader.use();
	program = uniformShader.program;
	mvp_matrix_loc = glGetUniformLocation(program, "mvp_matrix");
	color_loc = glGetUniformLocation(program, "color");
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
	glUniform4f(color_loc, 1.0, 1.0, 0.0, 0.0); //注意第四个元素是alpha，开启后0为透明
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
	glutCreateWindow("glsl-Uniform");
	GLenum status = glewInit();
	if (status != GLEW_OK)
		cerr << glewGetErrorString(status) << endl;
	init();
	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}