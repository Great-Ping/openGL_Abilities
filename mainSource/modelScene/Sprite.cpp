#include "Sprite.h"

shared_ptr <Mesh> Sprite::mesh;

Sprite::Sprite()
{

}

void Sprite::init()
{
	//������� ���
	mesh = make_shared<Mesh>("../AdditionalData/meshes/Sprite.obj");
}

void Sprite::setTexture(shared_ptr<Texture> texture)
{
	this->texture = texture;
}

void Sprite::draw(float left, float bottom, float width, float height) {

	// ������������ �������
	width *= 10;
	height *= 10;



	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
	//��������� ���������
	//glDisable(GL_LIGHTING);
	//��������� ��������� ��������� ������
	//glDisable(GL_CULL_FACE);
	//glDisable(GL_POLYGON_OFFSET_FILL);
	//�������� ��������� � ����� �����
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//������� ������� ������� ��� �������
	GLfloat modelMatrix[16] = {
		1.0, 0.0, 0.0, 0.0, // ��� Ox
		0.0, 1.25, 0.0, 0.0, // ��� Oy
		0.0, 0.0, 1.0, 0.0, // ��� Oz
		0.0, 0.75, 0.0, 0.0  // ������� ������� (������ ������� ���������)
	};
	

	// ��������� ��������
	// �������� �������� ���������� ����
	glActiveTexture(GL_TEXTURE0);
	// ��������� ��������������� � ��������� �������� ����������� �����
	glEnable(GL_TEXTURE_2D);
	
	// ��������� ����� ��������� �������� (GL_REPLACE)
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	// ����������� �������� � ����� ���������� ����������� �����
	(*texture).apply();

	//�������� �����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(modelMatrix);
	//���������� ���
	if (mesh != nullptr) {
		mesh->draw();
	}

	//�������� ���������
	//glEnable(GL_LIGHTING);
	//�������� ��������� ��������� ������
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_POLYGON_OFFSET_FILL);
	//��������� ���������
	//glDisable(GL_BLEND);
	//��������� ��������
	glDisable(GL_TEXTURE_2D);

	// ���������� ������� �������� � ���������� ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)1000 / 800, 0.2, 70.0);

}
