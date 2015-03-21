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
	  glVertex3f(-1.0f, -1.0f, 0.0f);
	  glVertex3f(1.0f, 0.0f, 0.0f);
	  glVertex3f(0.0, 1.0, 0.0);
	glEnd();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	float width = w, height = h;
	float ratio = width > height ? (width / height) : (height / width);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, ratio, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(720, 640);
	glutCreateWindow("Initialization");
	init();
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutMainLoop();
}