#pragma once
#include "../../../Header.h"

// ������� ����� ��� ���� ����������
class Material
{
public:
	// "����������" ���������
	virtual void apply(void) = 0;
};