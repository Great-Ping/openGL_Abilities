#pragma once
#include "../modelScene/Camera.h"
#include "../modelScene/GameObjectFactory.h"
#include "../modelScene/Light.h"
//������� ������� ��������
extern shared_ptr<GameObject> mapObjects[21][21];
extern shared_ptr<GameObject> field;

//������ 
extern Camera camera;

//����
extern Light light;

//����� ��������� ������ �����
extern double simTime;

//������ ��������� �������� ��������
extern double speedHorizontal; // ���� / c 
extern double speedVertical;
extern double speedZoom;

//������� ��� �������������
void initData();