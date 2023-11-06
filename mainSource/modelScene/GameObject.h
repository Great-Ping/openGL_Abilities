#pragma once
#include "../Header.h"
#include "graphicObject/GraphicObject.h"


// ����� ��� ����������� ���� �������� �������
enum class GameObjectType {
	FIELD, // ������� ����
	LIGHT_OBJECT, // ������ ������� ������
	HEAVY_OBJECT, // ������� ������� ������
	BORDER_OBJECT, // ��������� ������� ������
	PLAYER, // ������� ������ ��� ������������� ������
	BOMB, // ������� ������ ��� ������������� �����
	MONSTER // ������� ������ ��� ������������� ��������
};


// �����-������������ ��� �������� ����������� �����������
enum class MoveDirection { STOP, LEFT, RIGHT, UP, DOWN };

// ����� ��� ������������� �������� �������
class GameObject
{
public:
	// �����������
	GameObject();
	// ��������� ������������� ������������ �������
	// ���������� ����������� ����������� ������� ��� ������������ �������������
	void setGraphicObject(const GraphicObject& graphicObject);
	// ��������� ���������� ��������� (��� ������������� ������ ��� ��������)
	void setPosition(int x, int y);
	void setPosition(int x, int y, float z);
	void setPosition(ivec2 position);
	// ��������� ������� ���������� ���������
	ivec2 getPosition();

	// ������ �������� � ��������� ����������� � ��������� ���������
    // �������� ������������ ������������ ����������� ������ � �������
	void move(MoveDirection direction, float speed = 3.0f);
	// �������� �� ��, ��� ������ � ��������� ������ ��������
	bool isMoving();
	// ��������� �������� ������� (������� ����������� �������)
	// ����� ���������� ���������� � ������� simulation
	void simulate(float sec);

	// ����� �������� ������� �� �����
	void draw(void);
private:
	// ���������� ���������� �������� �������
	ivec2 position;
	// ����������� ������ (��� ������ �� �����)
	GraphicObject graphicObject;
	// ��������� ������� (�������� ����������� �����������)
	MoveDirection sost;
	// �������� � ����������� (�� 0.0 �� 1.0)
	float progress;
	// �������� �����������
	float speed;
};