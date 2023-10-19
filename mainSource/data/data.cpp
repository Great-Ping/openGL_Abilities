#include "data.h"

//������� ��� �������� ������� ��������
GameObjectFactory gameObjectFactory;
// ������ ������� �������� 
shared_ptr<GameObject> mapObjects[21][21];
shared_ptr<GameObject> field;
// ������������ ������
Camera camera(0, -50, -30);
// ���������� ����
Light light(20, 25, 15);
//����� ���������
double simTime;
//������ ��������
double speedHorizontal;
double speedVertical;
double speedZoom;
//���� � ����� � �������� ���������
string pathToGameObjects = "../AdditionalData/GameObjectType.json";
//����� ������������ ��� ����� �������� ������ 
int passabilityMap[21][21] = {
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,3,
3,0,2,1,2,0,2,0,2,2,2,1,2,0,2,0,2,0,2,2,3,
3,0,2,0,2,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,3,
3,0,1,0,2,2,1,2,2,0,2,0,2,2,2,1,2,0,2,0,3,
3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,0,3,
3,0,2,2,1,1,2,0,2,0,2,2,2,2,2,0,2,2,2,0,3,
3,0,2,0,0,0,2,0,2,0,0,0,0,0,2,0,0,0,0,0,3,
3,0,2,0,2,2,2,0,2,0,2,2,1,2,2,2,1,2,2,0,3,
3,0,0,0,2,0,0,0,2,0,2,0,0,0,0,0,0,0,1,0,3,
3,2,2,2,2,0,2,2,2,0,2,0,2,2,2,2,2,2,2,0,3,
3,0,0,0,2,0,0,0,1,0,2,0,0,0,2,0,0,0,0,0,3,
3,0,2,0,2,2,2,0,2,1,2,0,2,2,2,0,2,2,2,2,3,
3,0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,3,
3,2,2,2,2,0,2,2,2,0,2,2,2,0,1,0,2,2,2,0,3,
3,0,0,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,2,0,3,
3,0,2,0,2,1,2,0,2,0,2,2,2,0,2,2,2,0,2,0,3,
3,0,1,0,1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,3,
3,0,2,1,2,0,2,2,2,2,2,0,2,0,2,0,2,2,2,2,3,
3,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,3,
3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
};

void initData() 
{
	//�������� �������
	gameObjectFactory.init(pathToGameObjects);
	//������� ����
	field = gameObjectFactory.create(GameObjectType::FIELD, 10, 10);
	// ������������� �������� �����
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			switch (passabilityMap[i][j]) {
			case 1:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::LIGHT_OBJECT, j, i);
				break;
			case 2:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::HEAVY_OBJECT, j, i);
				break;
			case 3:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::BORDER_OBJECT, j, i);
				break;
			default:
				mapObjects[i][j] = nullptr;
				break;
			}
		}
	}

	//������������ ��������
	speedHorizontal = 90;
	speedVertical = 45;
	speedZoom = 5;

	//�������� �����
	light.setDiffuse(vec4(0.9, 0.9, 0.9, 1)); // ����
	light.setAmbient(vec4(0, 0, 0, 0)); // ��������� ����� �� ������ �������� (����������)
	light.setSpecular(vec4(0.5, 0.5, 0.5, 1)); // �����? �� � ��� ������� �� ����
}
