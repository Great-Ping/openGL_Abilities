#pragma once
#include "../modelScene/Camera.h"
#include "../modelScene/GameObject.h"
#include "../modelScene/Light.h"
//������ ����������� ��������
extern vector<GraphicObject> graphicObjects;

//������ ���������� ��������
extern vector<shared_ptr<PhongMaterial>> materials;

//������� ������� ��������
extern shared_ptr<GameObject> mapObjects[21][21];
//���� 
extern vector<shared_ptr<Mesh>> meshes;

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