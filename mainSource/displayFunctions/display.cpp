#include "display.h"

// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� �������� glutPostRedisplay

void display(void)
{
	// �������� ����� ����� � ����� �������
	glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �������� ���� �������
	glEnable(GL_DEPTH_TEST);

	// ������������� ��������� �� �������� ����������
	light.apply();

	// ������������� ������ �� �������� ����������
	camera.apply();
	
	(*player).draw();
	(*field).draw();
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			if(mapObjects[i][j] != nullptr) (*mapObjects[i][j]).draw();
		}
	}

	// ����� ��������� � ������� �������
	glutSwapBuffers();
};