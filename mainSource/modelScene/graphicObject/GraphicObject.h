#pragma once
#include "../../Header.h"
#include "graphicObjectComponents/PhongMaterial.h"
#include "graphicObjectComponents/Mesh.h"
#include "graphicObjectComponents/Texture.h"

// ����� ��� ������������� ������ ������������ �������
class GraphicObject
{
public:
	// �����������
	GraphicObject();
	// ��������� � ��������� ������� �������
	void setPosition(vec3 position);
	vec3 getPosition();
	// ��������� � ��������� ���� �������� � ��������
	// ������� �������������� � �������������� ���������
	// ������ ��� Oy �� ������� �������
	void setAngle(float grad);
	float getAngle();

	// ��������� �������� ����� �������
	void set�olor(vec3 color);
	vec3 getColor();
	// ��������� ������������� ���������
	void setMaterial(shared_ptr<PhongMaterial> material);
	// ��������� ������������� ����

	void setMesh(shared_ptr<Mesh> mesh);
	// ������� ������
	void draw();
private:
	// ������� ������� � ���������� ������� ���������
	vec3 position;
	// ���� �������� � �������������� ��������� (� ��������)
	float angle;
	// ���� ������
	vec3 color;
	// ������� ������ (������������ �������) - ���� �� ��������� ������ ���
	GLfloat* modelMatrix;
	// ������������ ��������
	shared_ptr<PhongMaterial> material;
	// ������������ ���
	shared_ptr<Mesh> mesh;
private:
	// ������ ������� modelMatrix �� ������ position � angle
	void recalculateModelMatrix();
};
