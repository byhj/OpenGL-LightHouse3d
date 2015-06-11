#include <GL/freeglut.h>

static float red, green, blue;
void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	static float angle = 0.0f;
	glLoadIdentity(); //每一次重置modelview矩阵，不然的话累积旋转矩阵会变得越来越快
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glColor3f(red, green, blue);
	glBegin(GL_TRIANGLES);
	  glVertex3f(-1.0f, -1.0f, 0.0f);
	  glVertex3f(1.0f, 0.0f, 0.0f);
	  glVertex3f(0.0, 1.0, 0.0);
	glEnd();
	angle += 0.1f;
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
}

void NormalKey(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
	else if (key == 'r') {
		int mod = glutGetModifiers();
	    if (mod = GLUT_ACTIVE_ALT) //ALT+R
		   red = 1.0;
		else
		   red = 0.0;
	}
}

void SpecialKey(int key, int x, int y)
{
	int mod;
	switch(key) {
	case GLUT_KEY_F1: {
		      mod = glutGetModifiers();
		      if (mod == (GLUT_ACTIVE_CTRL & GLUT_ACTIVE_ALT)) {
		     	 red = 1.0; green = 0.0; blue = 0.0;
		     }
    }
		   break;
	case GLUT_KEY_F2 :
		   red = 0.0;
		   green = 1.0;
		   blue = 0.0; break;
	case GLUT_KEY_F3 :
		   red = 0.0;
		   green = 0.0;
		   blue = 1.0; break;
	}
}
		

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(720, 640);
	glutCreateWindow("Initialization");
	init();
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutIdleFunc(render);
	glutKeyboardFunc(NormalKey);
	glutSpecialFunc(SpecialKey);
	glutMainLoop();
}