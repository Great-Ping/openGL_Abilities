#include "Texture.h"
#include <fstream>

Texture::Texture(string filename)
{
	load(filename);
}

//��������� �������� � ������� ���������� ������
void Texture::load(string filename)
{
	// ������� ����� "�����������"
	ILuint imageId = ilGenImage();
	// ������ ������� "�����������"
	ilBindImage(imageId);

	// ��������� �����������
	wchar_t unicodeString[256];
	wsprintf(unicodeString, L"%S", filename.c_str());

	if (ilLoadImage(unicodeString))
	{
		// ��������� ���������� ����������� ��������
		int width = ilGetInteger(IL_IMAGE_WIDTH);
		int height = ilGetInteger(IL_IMAGE_HEIGHT);

		char* data = new char[width * height * 4];

		ilCopyPixels(0, 0, 0, width, height, 1, IL_RGBA, IL_UNSIGNED_BYTE, data);
		ilDeleteImage(imageId);
		// ���������� ������ ������ (��������� ����������)
		glActiveTexture(GL_TEXTURE0);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		// ������� ���������� ������
		glGenTextures(1, &texIndex);
		//�������� ����������� ������� � �������� ����������� �����.
		glBindTexture(GL_TEXTURE_2D, texIndex);

		//�������� ����������� �� ����������� ������ � ���������� ������ � ��������� ������
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		//������� ������
		delete[] data;
	}
}

void Texture::apply(TextureFilter texFilter)
{
	
	switch (texFilter) {
	case TextureFilter::POINT:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	case TextureFilter::BILINEAR:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case TextureFilter::TRILINEAR:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case TextureFilter::ANISOTROPIC:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
		break;
	}
	glBindTexture(GL_TEXTURE_2D, texIndex);
}

void Texture::disableAll()
{
	glDisable(GL_TEXTURE_2D);
}
