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

//初始测试
void myDisplay(void) {
	//gl开头的函数为opengl本身的
	//glClear，清除。GL_COLOR_BUFFER_BIT表示清除颜色
	glClear(GL_COLOR_BUFFER_BIT);
	//glRectf，画一个矩形。四个参数分别表示了位于对角线上的两个点的横、纵坐标。
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	//glFlush，保证前面的OpenGL命令立即执行（而不是让它们在缓冲区中等待）。其作用跟fflush(stdout)类似
	glFlush();
}
//画点画线
void paintPoint(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	//颜色为红rgb
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(10);
	glBegin(GL_POINTS);
		glVertex2f(0.0f,0.1f);
	glEnd();
	//颜色为红rgb
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(0.0f,-0.1f);
	glEnd();
	//颜色为绿色
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(1, 1);
	//颜色为青绿
	glColor3f(0.0, 1.0, 1.0);
	glVertex2i(-1, -1);
	glEnd();
	//颜色为黄色
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(10);
	glBegin(GL_LINES);
	glVertex2i(1, -1);
	//颜色二为紫红
	glColor3f(1.0, 0.0, 1.0);
	glVertex2i(-1, 1);
	glEnd();

	glFlush();
}

//画三角形（list方法）
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
//画三角形（fans方法）
void paintTriangle_fans(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	//使用glPolygonMode对多边形设置绘制方式，分别为GL_FILL（填充），GL_LINE（轮廓）和（GL_POINT）定点绘制
	//且可对多边形正面，反面分别绘制
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//扇形绘制从中心开始，前三个顶点逆时针构成第一个三角形，从第三个顶点开始满足（n，中心，n-1）
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
//画三角形（stripes方法）
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
//画矩形，使用glRectf，也可以使用GL_QUADS给四个坐标点绘制一个四边形
void paintRectf(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	movex += offsetx;
	movey += offsety;
	offsetx = 0;
	offsety = 0;
	//定义当前摄像机位置和其视角，摄像机位于z轴上，目标位于原点，看向y轴正半轴(第三个参数定义观察者正对着的世界坐标系中的位置,即视野的中心)
	gluLookAt(
		movex, movey, 3.0,
		movex, movey, 0.0,
		0.0, 1.0, 0.0);

	//旋转核心代码
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
	//用于双缓冲，切换缓冲区
	glutSwapBuffers();
}

void resize(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*
	 *函数原型为glViewport(GLint x,GLint y,GLsizei width,GLsizei height)
	 * x，y以像素为单位，指定了窗口的左下角位置。width表示视口矩形的宽度和高度，根据窗口的实时变化重绘窗口
	*/
	glViewport(0, 0, w, h);

	/*
	 *gluPerspective有4个参数，
	 *gluPerspective(GLdouble fovy,GLdouble aspect,GLdouble zNear,GLdouble zFar);
	 * 第一个参数fovy定义可视角的大小(符合人眼的条件一般设置为40-70之间)。第二个参数aspect定义物体显示在画板上的x和y方向上的比例小于1则更高，大于1则更宽，等于1则显示正常长宽比。
	 * 第三个参数zNear定义距离相机最近处物体截面相距距离，若物体运动到距离观测点的距离小于zNear则不会被绘制到画布上。
	 * 第四个参数zFar定义了可观测物体最远处截面相距相机的距离。若物体运动到距离观测点的距离大于了设定的zFar则不会被绘制
	*/
	gluPerspective(45.0, 1.0 * w / h, 1.0, 100.0);

	/*
	 *glMatrixMode() 用以指定当前要操作的矩阵，可选值有GL_MODELVIEW（模型视图，默认值），GL_PROJECTION（投影），GL_TEXTURE（纹理），GL_COLOR（颜色）
	*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//与鼠标交互，当鼠标时间发生时会调用注册的函数，并向其提供这些参数值
//button的值有GLUT_LEFT_BUTTON、GLUT_MIDDLE_BUTTON、GLUT_RIGHT_BUTTON
//state的值有GLUT_UP、GLUT_DOWN
//x，y指明时间发生时鼠标的位置
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouseDown = true;
		xdiff = x - yrot;
		ydiff = -y + xrot;
	}
	else
		mouseDown = false;
}

//鼠标拖动事件，仅有两个参数，x，y表示鼠标所在的坐标
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
	//glut开头函数为glut自带的
	//对glut进行初始化，在使用其他glut命令前必须使用该语句（语句不变，复制即可）。
	glutInit(&argc, argv);
	////设置显示方式，GLUT_RGB表示使用RGB颜色，GLUT_SINGLE表示使用单缓冲
	//glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	////设置窗口在屏幕中的位置
	//glutInitWindowPosition(100, 100);
	////设置窗口大小
	//glutInitWindowSize(400, 400);
	////根据前面设置的信息创建窗口，参数将作为窗口的标题，只有使用了glutMainLoop()窗口才能显示
	//glutCreateWindow("第一个Opengl程序");
	////设置一个函数，当需要进行画图时，这个函数就会被调用。当画图时调用myDisplay
	//glutDisplayFunc(&myDisplay);
	////进行一个消息循环。
	//glutMainLoop();

/******************************************************************从这开始第一个练习***************************************************************************************/
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("旋转");


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