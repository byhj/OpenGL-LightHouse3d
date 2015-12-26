#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ogl/shader.h>

Shader toonShader("toon Shading");
GLuint program;

void init_shader()
{
	toonShader.init();
	toonShader.attach(GL_VERTEX_SHADER, "toon3.vert");
	toonShader.attach(GL_FRAGMENT_SHADER, "toon3.frag");
	toonShader.link();
	toonShader.use();
	program = toonShader.GetProgram();
}
void init()
{
	init_shader();
	float lpos[4] = {1, 0.5 , 1 ,0};
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
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
	glutCreateWindow("toon");
	glewInit();
	init();
	glutDisplayFunc(render);
	glutMainLoop();
}
