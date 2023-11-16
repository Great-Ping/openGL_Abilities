#include "Mesh.h"
#include "fstream"
#include <sstream>
#include <map>
#include <cstddef>
// ���������, ����������� ���� ������� ������������� �����
// ������ ������� ����� �������������� ����������,
// ������ ������� � ���������� ����������


Mesh::Mesh()
{

}

Mesh::Mesh(string filename)
{
	load(filename);

}

void Mesh::load(string filename)
{	
	// ������ ��� �������� �������������� ���������
	vector<vec3> vect;
	// ������ ��� �������� ��������
	vector<vec3> normal;
	// ������ ��� �������� ���������� ���������
	vector<vec2> texture;
	// ������ ��� �������� �������� ���������, ��� ���������� ������
	vector<ivec3> fPoints;
	// ������� ��� �������� 
	map<string, int> vertexToIndexTable;
	// ������ ������ ������������� �����
	vector<Vertex> vertices;
	// ������ ��������
	vector<GLuint> indices;
	int index = 0;
	

	fstream f(filename);
	if (!f.is_open()) {
		cout << "������ �������� .obj �����\n";
	}
	string lineStr;
	while (getline(f, lineStr)) {
		//�������� �� ������ ������
		if (lineStr.empty() || lineStr[0] == '#') continue;
		//��������� �� ��������� �����
		//���������� ����������� ����� ��� ������ �� ��������
		istringstream str(lineStr);
		//��� ������ (v, vn, vt)
		string type;
		str >> type;
		if (type == "v") {
			vec3 temp;
			str >> temp.x >> temp.y >> temp.z;
			vect.push_back(temp);
		}
		if (type == "vn") {
			vec3 temp;
			str >> temp.x >> temp.y >> temp.z;
			normal.push_back(temp);
		}
		if (type == "vt") {
			vec3 temp;
			str >> temp.x >> temp.y >> temp.z;
			texture.push_back(temp);
		}
		if (type == "f") {
			ivec3 temp;
			string strin;
			for (int i = 0; i < 3; i++) {
				str >> strin;
				//��������� �� ���������� � �������
				auto it = vertexToIndexTable.find(strin);
				if (it == vertexToIndexTable.end()) {
					vertexToIndexTable[strin] = index;
					indices.push_back(index);
					//���������� � fPoints
					replace(strin.begin(), strin.end(), '/', ' ');
					istringstream tempStr(strin);
					tempStr >> temp.x >> temp.y >> temp.z;
					fPoints.push_back(temp);

					index++;
				}
				else { 
					int pastIndex = (*it).second;
					indices.push_back(pastIndex);
				}
			}
		}
	}
	//testOutPut(fPoints);
	//������� ������� 
	int vectorLen = fPoints.size();
	for (int i = 0; i < vectorLen; i++) {
		Vertex tempVertex;
		int indexVert = fPoints[i][0] - 1;
		int indexNormal = fPoints[i][2] - 1;
		int indexTexture = fPoints[i][1] - 1;
		//cout << "������� ������� ������� " << indexVert<< " " << indexNormal  << " " << indexTexture << endl;
		// ���������� � ������� ������ �� ��������
		for (int j = 0; j < 3; j++) {
			tempVertex.coord[j] = vect[indexVert][j];
			tempVertex.normal[j] = normal[indexNormal][j];
		}
		for (int j = 0; j < 2; j++) {
			tempVertex.texCoord[j] = texture[indexTexture][j];
		}
		vertices.push_back(tempVertex);
	}

	glGenBuffers(1, &bufferIds[0]);
	glBindBuffer(GL_ARRAY_BUFFER, bufferIds[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &bufferIds[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIds[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()* sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	indexCount = indices.size();
}

void Mesh::draw()
{	
	//��������� �������� ���� ������ 
	glBindBuffer(GL_ARRAY_BUFFER, bufferIds[0]);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, coord));

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIds[1]);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}