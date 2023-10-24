#pragma once
#include "../modelScene/Camera.h"
#include "../modelScene/GameObjectFactory.h"
#include "../modelScene/Light.h"
//������� ������� ��������
extern shared_ptr<GameObject> mapObjects[21][21];
extern shared_ptr<GameObject> field;
extern shared_ptr<GameObject> player;
extern shared_ptr<GameObject> monsters[3];
//������ 
extern Camera camera;

//����
extern Light light;

//����� ������������
extern int passabilityMap[21][21];
//�������� ����� ������������
// 0 - ������ �����
// 1 - ������ ������, ������� ����� ���������� �����, �� �� ����� �������
// 2 - ������� ������
// 3 - ������
//����� ��������� ������ �����
extern double simTime;

//������ ��������� �������� ��������
extern double speedHorizontal; // ���� / c 
extern double speedVertical;
extern double speedZoom;

//������� ��� �������������
void initData();