#pragma once
#include "../Header.h"
#include "GameObject.h"
#include "map"

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


// ����� ��� �������� ������� ��������
class GameObjectFactory
{
public:
	// ������������� ������� (�������� ����� � ��������� ���������� ���������)
	void init(string filename);
	// �������� ������ ������� ��������� ����
	shared_ptr<GameObject> create(GameObjectType type, int x, int y);
private:
	// ���� ��� ������� ���� �������
	vector<shared_ptr<Mesh>> meshes;
	// ��������� ��� ������� ���� �������
	vector<shared_ptr<PhongMaterial>> materials;
};