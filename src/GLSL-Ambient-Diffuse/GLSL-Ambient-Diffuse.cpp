#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ogl/shader.h>

Shader diffuseShader("diffuse Shading");
GLuint program;

void init_shader()
{
	diffuseShader.init();
	diffuseShader.attach(GL_VERTEX_SHADER, "diffuse.vert");
	diffuseShader.attach(GL_FRAGMENT_SHADER, "diffuse.frag");
	diffuseShader.link();
	diffuseShader.use();
	program = diffuseShader.GetProgram();
}
void init()
{
	init_shader();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glutSolidTeapot(1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glutSwapBuffers();
}

int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(720, 640);
	glutCreateWindow("diffuse");
	glewInit();
	init();
	glutDisplayFunc(render);
	glutMainLoop();
}
