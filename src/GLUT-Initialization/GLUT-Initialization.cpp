#include <GL/freeglut.h>

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	  glVertex3f(-0.5f, -0.5f, 0.0f);
	  glVertex3f(0.5f, 0.0f, 0.0f);
	  glVertex3f(0.0, 0.5, 0.0);
	glEnd();
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(720, 640);
	glutCreateWindow("Initialization");
	init();
	glutDisplayFunc(render);
	glutMainLoop();
}