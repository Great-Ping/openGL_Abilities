#include "data.h"

// ������ ������� �������� 
shared_ptr<GameObject> mapObjects[21][21];
// ������ ����������� ��������
vector<GraphicObject> graphicObjects;
//������ ���������� �� ��������� ��������
vector<shared_ptr<PhongMaterial>> materials;
//������������ ���� 
vector<shared_ptr<Mesh>> meshes;
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
//���� � ����� � �����������
string pathToMaterial = "../AdditionalData/materials.json";
//����������� ���������
vector <int> materialId = {7, 6, 5, 8};
//���� � ����� � ������ ( �������� ������ )
string pathToMesh = "..//AdditionalData/meshes/";
//����������� ���� 
vector <string> meshNames = { "Box", "ChamferBox", "SimplePlane" };
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
	// ������������� ������, ����������� ��� ������ ���������:
	speedHorizontal = 90;
	speedVertical = 45;
	speedZoom = 5;

	//�������� �����
	light.setDiffuse(vec4(0.9, 0.9, 0.9, 1)); // ����
	light.setAmbient(vec4(0, 0, 0, 0)); // ��������� ����� �� ������ �������� (����������)
	light.setSpecular(vec4(0.5, 0.5, 0.5, 1)); // �����? �� � ��� ������� �� ����

	//��������� ����������� ���� �� ����� � �������
	for (int i = 0; i < meshNames.size(); i++) {
		shared_ptr<Mesh> tempMesh(new Mesh(pathToMesh + meshNames[i] + ".obj"));
		meshes.push_back(tempMesh);
	}

	//��������� ��������� �� ����� � �������
	for (int i = 0; i < materialId.size(); i++) {
		shared_ptr<PhongMaterial> tempPhongMaterial(new PhongMaterial(pathToMaterial, materialId[i] - 1));
		materials.push_back(tempPhongMaterial);
	}
	
	// ������������� ����������� ��������
	GraphicObject tempGraphicObject;
	//��� ������
	/*tempGraphicObject.setPosition(vec3(0, 0, 0));
	tempGraphicObject.setMaterial(materials[3]);
	graphicObjects.push_back(tempGraphicObject);*/

	//1 ��������� 
	tempGraphicObject.setPosition(vec3(0, -0.5, 0));
	tempGraphicObject.setMaterial(materials[3]);
	tempGraphicObject.setMesh(meshes[2]);
	graphicObjects.push_back(tempGraphicObject);
	//2 ������ ������� ��� - ������ "������" ����� (ChamferBox)
	tempGraphicObject.setPosition(vec3(-5, 0, 0));
	tempGraphicObject.setMaterial(materials[2]);
	tempGraphicObject.setMesh(meshes[1]);
	graphicObjects.push_back(tempGraphicObject);
	//3 ������ ������� ��� - ����� ������� ����� 
	tempGraphicObject.setPosition(vec3(0, 0, 5));
	tempGraphicObject.setMaterial(materials[1]);
	tempGraphicObject.setMesh(meshes[0]);
	graphicObjects.push_back(tempGraphicObject);
	//4 ������ ������� ��� - ������ ������� �����
	tempGraphicObject.setPosition(vec3(0, 0, -5));
	tempGraphicObject.setMaterial(materials[0]);
	tempGraphicObject.setMesh(meshes[0]);
	graphicObjects.push_back(tempGraphicObject);
	
	// ������������� �������� ����
	int type;
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			shared_ptr<GameObject> tempGameObject(new GameObject);
			type = passabilityMap[i][j];
			if (type != 0) {
				(*tempGameObject).setGraphicObject(graphicObjects[passabilityMap[i][j]]);
				(*tempGameObject).setPosition(j, i);
				mapObjects[i][j] = tempGameObject;
			}
			else mapObjects[i][j] = nullptr;
		}
	}
}
