#pragma once
#include "../../Header.h"
#include "../GameObject.h"
#include "map"


// ����� ��� �������� ������� ��������
class GameObjectFactory
{
public:
	// ������������� ������� (�������� ����� � ��������� ���������� ���������)
	void init(string filename);
	// �������� ������ ������� ��������� ����
	shared_ptr<GameObject> create(GameObjectType type, int x, int y, float z = 0);
private:
	// ���� ��� ������� ���� �������
	vector<shared_ptr<Mesh>> meshes;
	// ��������� ��� ������� ���� �������
	vector<shared_ptr<Material>> materials;
};