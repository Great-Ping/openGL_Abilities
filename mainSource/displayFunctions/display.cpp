#include "display.h"

// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� �������� glutPostRedisplay

void drawField();

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
	// ������ ��������
	for (int i = 0; i < 3; i++) {
		if (monsters[i] != nullptr) (*monsters[i]).draw();
	}
	// ������ ������ ���� �� ���� �� ���� 
	if(player != nullptr) (*player).draw();
	
	// ������ ����� 
	if (bomb != nullptr) {
		(*bomb).draw();
	}
	// ������ ����
	(*field).draw();
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			if(mapObjects[i][j] != nullptr) (*mapObjects[i][j]).draw();
		}
	}
	
	for (Decal item : decals) item.draw();
	
	// ����� ��������� � ������� �������
	glutSwapBuffers();
};

void drawField() {
	// �������� �������� ���������� ����
	glActiveTexture(GL_TEXTURE0);
	// ��������� ��������������� � ��������� �������� ����������� �����
	glEnable(GL_TEXTURE_2D);
	// ����������� �������� � ����� ���������� ����������� �����
	//planeTexture.apply();
	// ��������� ����� ��������� �������� (GL_MODULATE)
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// ������� ���������
	(*field).draw();
	// ��������� ��������������� (����� ��� ��������� ������� ���������� ��� �������)
	Texture::disableAll();
}