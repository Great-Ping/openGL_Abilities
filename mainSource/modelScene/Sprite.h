#pragma once
#include "graphicObject/GraphicObject.h"

// ����� ��� ������ �� ��������
class Sprite
{
public:
	// ����������� �� ���������
	Sprite();
	// ������� ������������� ����������� ����� - �������� ���� ��� �������
	static void init();
	// ������� ��������
	void setTexture(shared_ptr<Texture> texture);
	// ������� ��� ������ �������: ������ ����� ���� � �������
	// ����������� � ������������� �������� (0.0 - 1.0)
	void draw(float left, float bottom, float width, float height);
private:
	// ����� ��� ��� ���� ��������
	static shared_ptr <Mesh> mesh;
	// ��������, ������������ ��� ������� �������
	shared_ptr <Texture> texture;
};