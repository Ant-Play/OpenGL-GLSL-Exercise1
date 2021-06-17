#include <GL/glut.h>
#include <cmath>
#include <iostream>
#define PI 3.1415926536f

using namespace std;

bool mouseDown = false;
GLfloat	xrot = 0;
GLfloat	yrot = 0;

GLfloat	xdiff = 0;
GLfloat ydiff = 0;

GLfloat movex = 0;
GLfloat movey = 0;
GLfloat offsetx = 0;
GLfloat offsety = 0;

//��ʼ����
void myDisplay(void) {
	//gl��ͷ�ĺ���Ϊopengl�����
	//glClear�������GL_COLOR_BUFFER_BIT��ʾ�����ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	//glRectf����һ�����Ρ��ĸ������ֱ��ʾ��λ�ڶԽ����ϵ�������ĺᡢ�����ꡣ
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	//glFlush����֤ǰ���OpenGL��������ִ�У��������������ڻ������еȴ����������ø�fflush(stdout)����
	glFlush();
}
//���㻭��
void paintPoint(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	//��ɫΪ��rgb
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(10);
	glBegin(GL_POINTS);
		glVertex2f(0.0f,0.1f);
	glEnd();
	//��ɫΪ��rgb
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(0.0f,-0.1f);
	glEnd();
	//��ɫΪ��ɫ
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(1, 1);
	//��ɫΪ����
	glColor3f(0.0, 1.0, 1.0);
	glVertex2i(-1, -1);
	glEnd();
	//��ɫΪ��ɫ
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(10);
	glBegin(GL_LINES);
	glVertex2i(1, -1);
	//��ɫ��Ϊ�Ϻ�
	glColor3f(1.0, 0.0, 1.0);
	glVertex2i(-1, 1);
	glEnd();

	glFlush();
}

//�������Σ�list������
void paintTriangle_list(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_TRIANGLES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.1f, 0.1f);
		glVertex2f(0.2f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex2f(0.3f, 0.0f);
		glVertex2f(0.4f, 0.1f);
		glVertex2f(0.5f, 0.0f);
	glEnd();

	glFlush();
}
//�������Σ�fans������
void paintTriangle_fans(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	//ʹ��glPolygonMode�Զ�������û��Ʒ�ʽ���ֱ�ΪGL_FILL����䣩��GL_LINE���������ͣ�GL_POINT���������
	//�ҿɶԶ�������棬����ֱ����
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//���λ��ƴ����Ŀ�ʼ��ǰ����������ʱ�빹�ɵ�һ�������Σ��ӵ��������㿪ʼ���㣨n�����ģ�n-1��
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, -0.1f);
		glVertex2f(0.1f, 0.0f);
		glVertex2f(0.0f, 0.1f);
		glVertex2f(-0.1f, 0.0f);
		glVertex2f(0.0f, -0.1f);

	//glEnd();


	glFlush();
}
//�������Σ�stripes������
void paintTriangle_stripes(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(-0.2f, 0.1f);
		glVertex2f(-0.1f, 0.0f);
		glVertex2f(0.0f, 0.1f);
		glVertex2f(0.1f, 0.0f);
		glVertex2f(0.2f, 0.1f);
	glEnd();

	glFlush();
}
//�����Σ�ʹ��glRectf��Ҳ����ʹ��GL_QUADS���ĸ���������һ���ı���
void paintRectf(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	movex += offsetx;
	movey += offsety;
	offsetx = 0;
	offsety = 0;
	//���嵱ǰ�����λ�ú����ӽǣ������λ��z���ϣ�Ŀ��λ��ԭ�㣬����y��������(��������������۲��������ŵ���������ϵ�е�λ��,����Ұ������)
	gluLookAt(
		movex, movey, 3.0,
		movex, movey, 0.0,
		0.0, 1.0, 0.0);

	//��ת���Ĵ���
	glRotatef(xrot, 1.0, 0.0, 0.0);
	glRotatef(yrot, 0.0, 1.0, 0.0);


	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
		glVertex2f(-0.5, -0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(-0.5, 0.5);
	glEnd();

	glFlush();
	//����˫���壬�л�������
	glutSwapBuffers();
}

void resize(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*
	 *����ԭ��ΪglViewport(GLint x,GLint y,GLsizei width,GLsizei height)
	 * x��y������Ϊ��λ��ָ���˴��ڵ����½�λ�á�width��ʾ�ӿھ��εĿ�Ⱥ͸߶ȣ����ݴ��ڵ�ʵʱ�仯�ػ洰��
	*/
	glViewport(0, 0, w, h);

	/*
	 *gluPerspective��4��������
	 *gluPerspective(GLdouble fovy,GLdouble aspect,GLdouble zNear,GLdouble zFar);
	 * ��һ������fovy������ӽǵĴ�С(�������۵�����һ������Ϊ40-70֮��)���ڶ�������aspect����������ʾ�ڻ����ϵ�x��y�����ϵı���С��1����ߣ�����1���������1����ʾ��������ȡ�
	 * ����������zNear���������������������������룬�������˶�������۲��ľ���С��zNear�򲻻ᱻ���Ƶ������ϡ�
	 * ���ĸ�����zFar�����˿ɹ۲�������Զ�������������ľ��롣�������˶�������۲��ľ���������趨��zFar�򲻻ᱻ����
	*/
	gluPerspective(45.0, 1.0 * w / h, 1.0, 100.0);

	/*
	 *glMatrixMode() ����ָ����ǰҪ�����ľ��󣬿�ѡֵ��GL_MODELVIEW��ģ����ͼ��Ĭ��ֵ����GL_PROJECTION��ͶӰ����GL_TEXTURE��������GL_COLOR����ɫ��
	*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//����꽻���������ʱ�䷢��ʱ�����ע��ĺ������������ṩ��Щ����ֵ
//button��ֵ��GLUT_LEFT_BUTTON��GLUT_MIDDLE_BUTTON��GLUT_RIGHT_BUTTON
//state��ֵ��GLUT_UP��GLUT_DOWN
//x��yָ��ʱ�䷢��ʱ����λ��
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouseDown = true;
		xdiff = x - yrot;
		ydiff = -y + xrot;
	}
	else
		mouseDown = false;
}

//����϶��¼�����������������x��y��ʾ������ڵ�����
void mouseMotion(int x, int y) {
	if (mouseDown) {
		yrot = x - xdiff;
		xrot = y + ydiff;

		glutPostRedisplay();
	}
}

void keyboardFunc(unsigned char key, int x, int y) {
	switch (key){
		case 'd':
			offsetx = 0.005f;
			break;
		case 'a':
			offsetx = -0.005f;
			break;
		case 'w':
			offsety = 0.005f;
			break;
		case 's':
			offsety = -0.005f;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}
int main(int argc, char* argv[]) {
	//glut��ͷ����Ϊglut�Դ���
	//��glut���г�ʼ������ʹ������glut����ǰ����ʹ�ø���䣨��䲻�䣬���Ƽ��ɣ���
	glutInit(&argc, argv);
	////������ʾ��ʽ��GLUT_RGB��ʾʹ��RGB��ɫ��GLUT_SINGLE��ʾʹ�õ�����
	//glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	////���ô�������Ļ�е�λ��
	//glutInitWindowPosition(100, 100);
	////���ô��ڴ�С
	//glutInitWindowSize(400, 400);
	////����ǰ�����õ���Ϣ�������ڣ���������Ϊ���ڵı��⣬ֻ��ʹ����glutMainLoop()���ڲ�����ʾ
	//glutCreateWindow("��һ��Opengl����");
	////����һ������������Ҫ���л�ͼʱ����������ͻᱻ���á�����ͼʱ����myDisplay
	//glutDisplayFunc(&myDisplay);
	////����һ����Ϣѭ����
	//glutMainLoop();

/******************************************************************���⿪ʼ��һ����ϰ***************************************************************************************/
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("��ת");


	glutDisplayFunc(paintRectf);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboardFunc);

	glClearColor(0.93f, 0.93f, 0.93f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);

	glutMainLoop();
	
	return 0;
}