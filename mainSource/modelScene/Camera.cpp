#include "Camera.h"
#define CORRECTION 3.14159265 / 180
Camera::Camera()
{
	setPosition(vec3(0, 0, 0));
}

Camera::Camera(vec3 position)
{
	setPosition(position);
}

Camera::Camera(float x, float y, float z)
{
	setPosition(vec3(x, y, z));
}

void Camera::setPosition(vec3 position)
{
	//������������� ������������ ����������
	// ���������� ������ - ���������� �� ������ ������� ��������� �� �������� �������
	r = length(position);
	// ���������� ������������ ����:
	// ��� ���� ����� �������� �� ������ ��������� � ����������� (v1)
	// � ��������� ����� ������� �� �������������� ��������� (v2)
	// ��� ����������� ���� ������������ ��������� ������������ ��������������� ��������
	vec3 v1 = position;
	vec3 v2 = vec3(v1.x, 0, v1.z);
	float cos_y = dot(normalize(v1), normalize(v2));
	angleY = 90 - degrees(acos(cos_y));
	// ����������� ������� ���������� �������������� ����:
	// ��� ���� ����� ��������� (v2) � ��������� �������� ����� ��� Ox
	float cos_x = dot(normalize(v2), vec3(1, 0, 0));
	angleX = degrees(acos(cos_x));
	// ������������� ������� (��� ������������� ������ ����������)
	recalculatePosition();
}

vec3 Camera::getPosition()
{
	return this->position;
}

void Camera::rotateLeftRight(float degree)
{
	angleX += degree;
	if (angleX >= 360) angleX -= 360;
	if (angleX <= -360) angleX += 360;
	recalculatePosition();
}

void Camera::rotateUpDown(float degree)
{	
	angleY -= degree;
	if (angleY < 5) angleY = 5;
	if (angleY > 90) angleY = 90;	 
	recalculatePosition();
}

void Camera::zoomInOut(float distance)
{
	r -= distance;
	recalculatePosition();
}

void Camera::apply()

{
	// ������������� ������
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position.x, position.y, position.z, 0, 0, 0, 0, 1, 0);
}

void Camera::recalculatePosition()
{
	position.x = r * sin(angleY * CORRECTION) * cos(angleX * CORRECTION);
	position.z = r * sin(angleY * CORRECTION) * sin(angleX * CORRECTION);
	position.y = r * cos(angleY * CORRECTION);
	//cout << position.x << " " << position.y << " " << position.z << endl;
}