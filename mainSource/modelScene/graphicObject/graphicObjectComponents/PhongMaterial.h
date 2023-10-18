#pragma once
#include "../../../Header.h"
#include "nlohmann/json.hpp"
#include <fstream>
// ����� ��� ������ � ����������
class PhongMaterial
{
public:
	// ����������� �� ���������
	PhongMaterial();
	PhongMaterial(string filename, int materialId);
	// ������� ���������� ���������
	void setAmbient(vec4 color);
	void setDiffuse(vec4 color);
	void setSpecular(vec4 color);
	void setEmission(vec4 color);
	void setShininess(float p);
	// �������� ���������� ��������� �� �������� ���������� �����
	void load(string filename, int materialId);
	// ��������� ���� ���������� ���������
	void apply();
private:
	// ������� ������������
	vec4 ambient;
	// ��������� ������������
	vec4 diffuse;
	// ���������� ������������
	vec4 specular;
	// ������������
	vec4 emission;
	// ������� ����������������
	float shininess;
};



