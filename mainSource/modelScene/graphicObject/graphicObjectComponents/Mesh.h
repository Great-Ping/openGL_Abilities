#pragma once
#include "../../../Header.h"

struct Vertex
{
	// �������������� ����������
	GLfloat coord[3];
	// ������ �������
	GLfloat normal[3];
	// ���������� ���������� �������� ����������� �����
	GLfloat texCoord[2];
};

// ����� ��� ������ C �����
class Mesh
{
public:
	// �����������
	Mesh();
	Mesh(string filename);
	// �������� ���� �� ����� � ��������� ������
	void load(string filename);
	// ����� ���� (�������� ���� ������ � OpenGL)
	void draw();
private:
	// ���������� ��������
	int indexCount;
	// ������� (��������������) ������� OpenGL
	GLuint bufferIds[2];
};
