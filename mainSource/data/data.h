#pragma once
#include "../modelScene/Camera.h"
#include "../modelScene/gameObjectTools/GameObjectFactory.h"
#include "../modelScene/Light.h"
#include "../modelScene/Decal.h"

extern GameObjectFactory gameObjectFactory;
//������� ������� ��������
extern shared_ptr<GameObject> mapObjects[21][21];
extern shared_ptr<GameObject> field;
extern shared_ptr<GameObject> player;
extern shared_ptr<GameObject> monsters[3];
extern shared_ptr<GameObject> bomb;
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
// 4 - ������
// 5 - ����� 

//����� ��������� ������ �����
extern double simTime;

//������ ��������� �������� ��������
extern double speedHorizontal; // ���� / c 
extern double speedVertical;
extern double speedZoom;

// ������
extern vector<Decal> decals;

//������� ��� �������������
void initData();