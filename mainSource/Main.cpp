#include "data/data.h"
#include "displayFunctions/display.h"
#include "displayFunctions/simulation.h"

int main(int argc, char** argv) 
{
	setlocale(LC_ALL, "ru");
	//�������������� ������
	initData();
	//������ ��������� �����
	StartCounter();
	// ������������� ���������� GLUT
	glutInit(&argc, argv);
	// ������������� ������� (������ ������)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// �������� ����:
	// 1. ������������� ������� ����� ���� ����
	glutInitWindowPosition(250, 10);
	// 2. ������������� ������ ����
	glutInitWindowSize(1000, 800);
	// 3. ������� ����
	glutCreateWindow("Laba_04");

	

	// ������������� ����� ������� ������������
	GLfloat globalAmbientColor[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor);


	// �������� ����� ������� ���������
	glEnable(GL_LIGHTING);
	// �������� ������ �������� �����
	glEnable(GL_LIGHT0);

	// ��������� ���������� �� OPENGL
	printf("GL_VENDOR = %s\n", glGetString(GL_VENDOR));
	printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
	printf("GL_VERSION = %s\n\n", glGetString(GL_VERSION));

	// ��������� ������� ��������� ������
	// ������������� �������, ������� ����� ���������� ��� ����������� ����
	glutDisplayFunc(display);
	// ������������� �������, ������� ����� ���������� ��� ��������� �������� ����
	glutReshapeFunc(reshape);
	// �������� ������� �� ���������� �������
	glutIdleFunc(simulation);

	// �������� ���� ��������� ��������� ��
	glutMainLoop();
	return 0;
};