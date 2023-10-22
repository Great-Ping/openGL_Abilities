#pragma once
#include "../../../Header.h"

// ������������ ��� ����������� ������ ����������
enum class TextureFilter {
	POINT, // ��������
	BILINEAR, // ����������
	TRILINEAR, // �����������
	ANISOTROPIC // ������������
};

// ����� ��� ������ � ���������
class Texture
{
public:
	// �������� �������� �� �������� �����
	void load(string filename);
	// ���������� �������� (�������� � ����������� ����� � ��������� ����������)
	void apply(TextureFilter texFilter = TextureFilter::ANISOTROPIC);
	// ���������� ��������������� ��� ���� ���������� ������
	static void disableAll();
private:
	// ������������� (������) ����������� �������
	GLuint texIndex;
};
