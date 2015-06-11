#include <GL/glew.h>
#include <GL/freeglut.h>
#include <shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Shader colorShader("glsl test");
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
	colorShader.init();
	colorShader.attach(GL_VERTEX_SHADER, "flatten.vert");
	colorShader.attach(GL_FRAGMENT_SHADER, "flatten.frag");
	colorShader.link();
	colorShader.use();
	program = colorShader.program;
	color_loc = glGetUniformLocation(program, "time");

}

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	init_shader();
	glEnable(GL_DEPTH_TEST);
}

static float ry = 0.0;

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);
	float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	glUniform1f(color_loc, time); //注意第四个元素是alpha，开启后0为透明
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(ry, 0.0, 1.0, 0.0);
	glutSolidTeapot(1.0f);
	ry += 0.1f;
	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 720.0 / 640.0, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);

}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(720, 640);
	glutCreateWindow("glsl-Shader-Example");
	GLenum status = glewInit();
	if (status != GLEW_OK)
		cerr << glewGetErrorString(status) << endl;
	init();
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}