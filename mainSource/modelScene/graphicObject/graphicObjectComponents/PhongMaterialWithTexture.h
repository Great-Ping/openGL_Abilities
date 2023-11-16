#pragma once
#include "Material.h"
#include "Texture.h"

// ����� ��� ������ � ����������
class PhongMaterialWithTexture : public Material
{
public:
	// ����������� �� ���������
	PhongMaterialWithTexture(string filename, int materialId);
	// ������� ���������� ���������
	void setAmbient(vec4 color);
	void setDiffuse(vec4 color);
	void setSpecular(vec4 color);
	void setEmission(vec4 color);
	void setShininess(float p);
	// ��������� ������������ ��������
	void setTexture(shared_ptr<Texture> texture);
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
	// ������������ ��������
	std::shared_ptr<Texture> texture;
};
