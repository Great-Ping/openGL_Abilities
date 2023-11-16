#include "Decal.h"

//��������� ����������� ���� ������
shared_ptr <PhongMaterialWithTexture> Decal::material;
shared_ptr <Mesh> Decal::mesh;

void Decal::init()
{
	//������� ��������
	material = make_shared<PhongMaterialWithTexture>("../AdditionalData/materials.json", 8);
	//������� ��������
	shared_ptr <Texture> tempTexture(new Texture("../AdditionalData/textures/decal.png"));
	(*material).setTexture(tempTexture);
	//������� ����
	mesh = make_shared<Mesh>("../AdditionalData/meshes/Decal.obj");
}

Decal::Decal()
{
	GraphicObject tempGraphicObject;
	tempGraphicObject.setMaterial(material);
	tempGraphicObject.setMesh(mesh);
	graphicObject = tempGraphicObject;
}

Decal::Decal(ivec2 position)
{
	this->position = position;
	GraphicObject tempGraphicObject;
	tempGraphicObject.setMaterial(material);
	tempGraphicObject.setMesh(mesh);
	tempGraphicObject.setPosition(vec3(position.x - 10, -0.49, position.y - 10));
	graphicObject = tempGraphicObject;
}

void Decal::setPosition(ivec2 position)
{
	this->position = position;
	graphicObject.setPosition(vec3(position.x - 10, -0.49, position.y - 10));

}

ivec2 Decal::getPosition()
{
	return position;
}
void Decal::draw()
{
	// �������� ����� ��������� ���������
	glEnable(GL_BLEND);
	// ������������� ������� ��������� � ���������
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	graphicObject.draw();
	//��������� ��������������� 
	Texture::disableAll();
	glDisable(GL_BLEND);
}
