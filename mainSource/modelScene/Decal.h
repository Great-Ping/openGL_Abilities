#pragma once
#include "graphicObject/GraphicObject.h"

// ����� ��� ������������� ������
class Decal
{
public:
	// ������� ������������� ����������� �����:
	// �������� ����, �������� �������� � �������� ���������
	static void init();
	// ������������: ��-��������� � � �������� ���������� ���������
	Decal();
	Decal(ivec2 position);
	// ��������� � ��������� ���������� ���������
	void setPosition(ivec2 position);
	ivec2 getPosition();
	// ����� ������
	void draw();
	
private:
	// ����������� ������ ��� ������������� ������
	GraphicObject graphicObject;
	// ���������� ������� ������
	ivec2 position;
	// ����� �������� ��� ���� �������
	static shared_ptr <PhongMaterialWithTexture> material;
	// ����� ��� ��� ���� �������
	static shared_ptr <Mesh> mesh;
};



