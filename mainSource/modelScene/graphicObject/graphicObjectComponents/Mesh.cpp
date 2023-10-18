#include "Mesh.h"
#include "fstream"
#include <sstream>
#include <map>
// ���������, ����������� ���� ������� ������������� �����
// ������ ������� ����� �������������� ����������,
// ������ ������� � ���������� ����������



void testOutPut(vector <ivec3> t) {
	for (ivec3 i : t) {
		for (int j = 0; j < 3; j++) cout << i[j] << ' ';
		cout << '\n';
	}
	cout << '\n';
}
void testOutPut(vector <vec3> t) {
	for (vec3 i : t) {
		for (int j = 0; j < 3; j++) cout << i[j] << ' ';
		cout << '\n';
	}
	cout << '\n';
}
void testOutPut(vector <vec2> t) {
	for (vec2 i : t) {
		for (int j = 0; j < 2; j++) cout << i[j] << ' ';
		cout << '\n';
	}
	cout << '\n';
}


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
		this->vertices.push_back(tempVertex);
	}
 
}

void Mesh::draw()
{	
	int vectorLen = vertices.size();
	// �������� �������� �� ������� ������ 
	// ��������� ������ ���������
	vec3* coordinateArray = new vec3[vectorLen];
	// ��������� ������ �������
	vec3* normalArray = new vec3[vectorLen];
	// ��������� ������ ���������� ���������
	vec2* textureCoordinateArray = new vec2[vectorLen];
	for (int i = 0; i < vectorLen; i++) {
		coordinateArray[i] = vec3(vertices[i].coord[0], vertices[i].coord[1], vertices[i].coord[2]);
		normalArray[i] = vec3(vertices[i].normal[0], vertices[i].normal[1], vertices[i].normal[2]);
		textureCoordinateArray[i] = vec2(vertices[i].texCoord[0], vertices[i].texCoord[1]);
	}

	//��������� �������� ���� ������ 
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, coordinateArray);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normalArray);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, textureCoordinateArray);
	//������� ��� �������
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());
	//glDrawArrays(GL_TRIANGLES, 0, vectorLen);
	//��������� ��������� ������� ������
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//������� �������
	delete[] coordinateArray;
	delete[] normalArray;
	delete[] textureCoordinateArray;

}