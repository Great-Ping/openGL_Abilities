#include "GraphicObject.h"

GraphicObject::GraphicObject()
{

	this->modelMatrix = new GLfloat[16]{
		1.0, 0.0, 0.0, 0.0, // ��� Ox
		0.0, 1.0, 0.0, 0.0, // ��� Oy
		0.0, 0.0, 1.0, 0.0, // ��� Oz
		0.0, 0.0, 0.0, 1.0  // ������� ������� (������ ������� ���������)
	};

	this->color = vec3(1, 0, 0);
	this->angle = 0;
}


void GraphicObject::setPosition(vec3 position)
{
	this->position = position;
	//�� ����� ����������� ������� 
	recalculateModelMatrix();
}

vec3 GraphicObject::getPosition()
{
	return this->position;
}

void GraphicObject::setAngle(float grad)
{
	this->angle = grad / 180 * 3.1415;//�� ����� ����������� ������� 
	recalculateModelMatrix();
}

float GraphicObject::getAngle()
{
	return this->angle;
}

void GraphicObject::set�olor(vec3 color) {
	this->color = color;
}

vec3 GraphicObject::getColor()
{
	return this->color;
}

void GraphicObject::setMaterial(shared_ptr<PhongMaterial> material)
{
	this->material = material;
}

void GraphicObject::setMesh(shared_ptr<Mesh> mesh)
{
	this->mesh = mesh;
}

void GraphicObject::draw()
{
	

	//��������� ���� �������
	glColor3f(color.r, color.g, color.b);

	//��������� �������� ��� �������
	if (material != nullptr) {
		material->apply();
	}

	glPushMatrix();
	glMultMatrixf(this->modelMatrix);
	//���������� ���
	if (mesh != nullptr) {
		mesh->draw();
	}
	else {
		glutSolidTeapot(1);
	}
	
	glPopMatrix();
}

void GraphicObject::recalculateModelMatrix()
{
	//�������� ������� 
	for (int i = 0; i < 3; i++) modelMatrix[12 + i] = position[i];
	//����������� ���� ��� �������� ������	������ ��� Y
	modelMatrix[0] = cos(angle);
	modelMatrix[2] = sin(angle);
	modelMatrix[8] = -sin(angle);
	modelMatrix[10] = cos(angle);
}

