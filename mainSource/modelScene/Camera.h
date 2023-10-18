#pragma once
#include "../Header.h"

// ����� ��� ������ � �������
class Camera
{
public:
	// ������������
	Camera();
	Camera(vec3 positi��on);
	Camera(float x, float y, float z);
	// ��������� � ��������� ������� ������
	void setPosition(vec3 position);
	vec3 getPosition();
	//������� ��� ����������� ������
	void rotateLeftRight(float degree);
	void rotateUpDown(float degree);
	void zoomInOut(float distance);
	// ������� ��� ��������� ������� ������
	void apply();
private:
	// ���������� ������� ������ ����� ���������
	void recalculatePosition();
private:
	// ������������ ����������
	float r; // ������ ��� � ��� ����
	float angleX; // ���� ��
	float angleY; // ���� ����
	// ���������� ����������
	vec3 position;
};

