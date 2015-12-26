#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ogl/shader.h>
#include <iostream>

using std::cerr; using std::endl;

static float camX, camY, camZ;
static glm::vec3 center = glm::vec3(0.0, 1.5, 0.0); 
int startX, startY, tracking = 0;
static float alpha = 330.0f, beta = 30.0f, r = 9.5f;

Shader selectionShader("selectShader");
Shader pickingShader("pickingShader");
GLuint selection_pro, picking_pro;
glm::vec4 lightPos = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
GLuint proj_matrix_loc, view_matrix_loc, model_matrix_loc;
GLuint diffuse_loc, code_loc;

static const glm::vec4 color[] =
{
	glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
	glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
	glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
	glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
};

void init_shader()
{
	selectionShader.init();
	selectionShader.attach(GL_VERTEX_SHADER, "selection.vert");
	selectionShader.attach(GL_FRAGMENT_SHADER, "selection.frag");
	selectionShader.link();
	selection_pro = selectionShader.GetProgram();
	code_loc = glGetUniformLocation(selection_pro, "code");
	pickingShader.init();
	pickingShader.attach(GL_VERTEX_SHADER, "picking.vert");
	pickingShader.attach(GL_FRAGMENT_SHADER, "picking.frag");
	pickingShader.link();
	picking_pro = pickingShader.GetProgram();
	diffuse_loc = glGetUniformLocation(picking_pro, "diffuse");
}
void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 view_matrix = glm::lookAt(glm::vec3(camX, camY, camZ), 
		                                center, glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 model_matrix = glm::mat4(1.0f);
	glUniformMatrix4fv(view_matrix_loc, 1, GL_FALSE, &view_matrix[0][0]);

	model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, -2.0f));
	glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, &model_matrix[0][0]);
	glUniform4fv(diffuse_loc, 1, &color[0][0]);
	//objRender();
	model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, &model_matrix[0][0]);
	glUniform4fv(diffuse_loc, 1, &color[1][0]);
	//objRender();
	model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-4.0f, 0.0f, 4.0f));
	glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, &model_matrix[0][0]);
	glUniform4fv(diffuse_loc, 1, &color[2][0]);
	//objRender();
	model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 0.0f, .0f));
	glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, &model_matrix[0][0]);
	glUniform4fv(diffuse_loc, 1, &color[3][0]);
//	objRender();

	glutSwapBuffers();
}

void renderSelection()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glm::mat4 view_matrix = glm::lookAt(glm::vec3(camX, camY, camZ), 
		                                center, glm::vec3(0.0, 1.0, 0.0));

	glm::mat4 model_matrix = glm::mat4(1.0f);
	glUniformMatrix4fv(view_matrix_loc, 1, GL_FALSE, &view_matrix[0][0]);

	model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, -2.0f));
	glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, &model_matrix[0][0]);
	glUniform1i(code_loc, 1);
	//objRender();
	model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, &model_matrix[0][0]);
	glUniform1i(code_loc, 2);
	//objRender();
	model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-4.0f, 0.0f, 4.0f));
	glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, &model_matrix[0][0]);
	glUniform1i(code_loc, 3);
	//objRender();
	model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 0.0f, .0f));
	glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, &model_matrix[0][0]);
	glUniform1i(code_loc, 4);
	//objRender();
}//

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glm::mat4 proj_matrix = glm::perspective(53.13f, 720.0f / 640.0f, 0.1f, 10000.0f);
	glUniformMatrix4fv(proj_matrix_loc, 1, GL_FALSE, &proj_matrix[0][0]); 
}

void sphereCoord(float r, float alpha, float beta) {

	camX = center[0] + r * sin(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camZ = center[2] + r * cos(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	camY = center[1] + r * sin(beta * 3.14f / 180.0f);
}

void mouseWheel(int wheel, int direction, int x, int y)
{
	r += direction;
	if (r < 0.1f)
		r = 0.1f;
	sphereCoord(r, alpha, beta);
	glutPostRedisplay();
}
void selection(int xx, int yy) {

	unsigned char res[4];
	GLint viewport[4]; 
	renderSelection();
	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadPixels(xx, viewport[3] - yy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &res);
	switch(res[0]) {
		case 0: printf("Nothing Picked \n"); break;
		case 1: printf("Picked yellow\n"); break;
		case 2: printf("Picked red\n"); break;
		case 3: printf("Picked green\n"); break;
		case 4: printf("Picked blue\n"); break;
		default:printf("Res: %d\n", res[0]);
	}
}

void mouseButton(int button, int state, int xx, int yy)
{
	if (state == GLUT_DOWN) {
		startX = xx;
		startY = yy;
		if (button == GLUT_RIGHT_BUTTON)
			tracking = 1;
		else if (button == GLUT_LEFT_BUTTON) {
			tracking = 0;
			selection(xx, yy);
		}
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha -= (xx - startX);
		    beta += (yy - startY);
			if (beta > 85.0f)
				beta = 85.0f;
			else if (beta < -85.0f)
				beta = -85.0f;
	   }
		tracking = 0;
	}
}
	    
void mouseMotion(int xx, int yy)
{
	if (!tracking)
		return;
	int deltaX, deltaY;
	float alphaAux, betaAux;
	float rAux;

	deltaX =  - xx + startX;
	deltaY =    yy - startY;

	alphaAux = alpha + deltaX;
	betaAux = beta + deltaY;

	if (betaAux > 85.0f)
		betaAux = 85.0f;
	else if (betaAux < -85.0f)
		betaAux = -85.0f;
	rAux = r;
	sphereCoord(rAux, alphaAux, betaAux);
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE);
	glutInitWindowPosition(300, 0);
	glutInitWindowSize(720, 640);
	glutCreateWindow("Picking Demo");
	GLenum status = glewInit();
	if (status != GLEW_OK)
		std::cerr << glewGetErrorString(status) << std::endl;
	init();
	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	glutMouseWheelFunc(mouseWheel);
	glutMainLoop();
}
