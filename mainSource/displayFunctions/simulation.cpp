#include "simulation.h"

double getSimulationTime();
void setWindowFPS();
void StartCounter();
int getFPS();
void cameraSimulation(float simulationTime);
void gameObjectSimulation(float simulationTime);
void movePlayer();
void movePlayerWithLightBlock(MoveDirection direction, int playerPositionX, int playerPositionY);
void monstersSimulation(float simTime); 
void randomizeDirection(MoveDirection& direction);
//������ ���������� ��� ������ �� ��������
double PCFreq = 0.0;
__int64 CounterStart = 0;
double summ = 0;
//������� ������� �� ���������� ������������
map<MoveDirection, ivec2> moveDirectionToVector = {
	{ MoveDirection::STOP,  ivec2(0,  0) },
	{ MoveDirection::UP,    ivec2(0, -1) },
	{ MoveDirection::LEFT,  ivec2(-1, 0) },
	{ MoveDirection::DOWN,  ivec2(0 , 1) },
	{ MoveDirection::RIGHT, ivec2(1,  0) }
};
// ������ ��������� ����� 
double monstersTimings[3] = {0, 0, 0};


void simulation() {
	float simTime = getSimulationTime();
	//��������� ������
	cameraSimulation(simTime);
	//��������� ���� ������� �������� ( �� ������� ����������� )
	gameObjectSimulation(simTime);
	//��������� ��������
	monstersSimulation(simTime);

	setWindowFPS();
	if (player != nullptr) {
		movePlayer();
	}
	
	// ������������� ������� ����, ��� ���� ��������� � �����������
	glutPostRedisplay();
};

void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

void reshape(int w, int h)
{
	// ���������� ����� ������� ���������, ������ ���� ������� ����
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// ���������� ������� �������� � ���������� ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

double getSimulationTime()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	simTime = double(li.QuadPart - CounterStart) / PCFreq;
	StartCounter();
	return simTime;
}

int getFPS()
{
	return (int)(1000 / simTime);
}

//������� ��������� �������� ������ 
void movePlayer() {
	MoveDirection direction = MoveDirection::STOP;
	//�������� ��������� ������� ������ 
	int playerPositionX = (*player).getPosition()[0];
	int playerPositionY = (*player).getPosition()[1];

	if (GetAsyncKeyState('W')) direction = MoveDirection::UP;
	if (GetAsyncKeyState('A')) direction = MoveDirection::LEFT;
	if (GetAsyncKeyState('S')) direction = MoveDirection::DOWN;
	if (GetAsyncKeyState('D')) direction = MoveDirection::RIGHT;
	//��������� �� ����������� ����������� � ���������� ������ ���������

	if (!(*player).isMoving() && direction != MoveDirection::STOP) {
		//������� ���������� ���� ������ � ������ �� ���
		ivec2 nextPLayerLocation = ivec2(playerPositionX + moveDirectionToVector[direction].x,
										 playerPositionY + moveDirectionToVector[direction].y);
		ivec2 LocationAcrossPlayer = ivec2(playerPositionX + 2 * moveDirectionToVector[direction].x,
										   playerPositionY + 2 * moveDirectionToVector[direction].y);

		//������� ���� ���� ������
		int nextLocationType = passabilityMap[nextPLayerLocation.x][nextPLayerLocation.y];
		int nextAcrossLocationType = passabilityMap[LocationAcrossPlayer.x][LocationAcrossPlayer.y];

		//��������� �������� �� �������������� ������� ��� ������������
		if (nextLocationType == 1 && nextAcrossLocationType == 0) {
			movePlayerWithLightBlock(direction, playerPositionX, playerPositionY);
			return;
		}
		//�������� �� ������� �����������
		if (nextLocationType == 0) (*player).move(direction);
	}
}

//���������� �������, ���� ���������� ?
void movePlayerWithLightBlock(MoveDirection direction, int playerPositionX, int playerPositionY) {

	ivec2 nextPosition;
	switch (direction)
	{
	case MoveDirection::STOP:
		nextPosition = ivec2(0, 0);
		break;
	case MoveDirection::LEFT:
		nextPosition = ivec2(-1, 0);
		break;
	case MoveDirection::RIGHT:
		nextPosition = ivec2(1, 0);
		break;
	case MoveDirection::UP:
		nextPosition = ivec2(0, -1);
		break;
	case MoveDirection::DOWN:
		nextPosition = ivec2(0, 1);
		break;
	}
	ivec2 nextDoublePosition = nextPosition * 2;

	(*player).move(direction);
	(*mapObjects[playerPositionX + nextPosition[0]][playerPositionY + nextPosition[1]]).move(direction);

	if ((*mapObjects[playerPositionX + nextPosition[0]][playerPositionY + nextPosition[1]]).isMoving() == false) {
		//�������� ����� ������������ 
		passabilityMap[playerPositionX + nextPosition[0]][playerPositionY + nextPosition[1]] = 0;
		passabilityMap[playerPositionX + nextDoublePosition[0]][playerPositionY + nextDoublePosition[1]] = 1;
		//�������� ������� �����
		mapObjects[playerPositionX + nextDoublePosition[0]][playerPositionY + nextDoublePosition[1]] = mapObjects[playerPositionX + nextPosition[0]][playerPositionY + nextPosition[1]];
		mapObjects[playerPositionX + nextPosition[0]][playerPositionY + nextPosition[1]] = nullptr;
	}
}

//������� ��� ������� �������� �������� 
void monstersSimulation(float simTime)
{	
	MoveDirection direction = MoveDirection::STOP;
	//������ ��������� �������� ��� ������� 
	for (int i = 0; i < 3; i++) {
		//������������ ��������
		monstersTimings[i] += simTime;
		// ������ ������� ��������� ����������� 
		if (monstersTimings[i] > 100) {
			monstersTimings[i] = 0;

			//��������� �� ����� �� ������ � ������ 
			if (player != nullptr) {
				if ((*monsters[i]).getPosition() == (*player).getPosition()) {
					//������� ������
					player.reset();
				}
			}
			
			//�������� ����������� �������� 
			randomizeDirection(direction);

			if (!(*monsters[i]).isMoving() && direction != MoveDirection::STOP) {
				//������� ���������� ���� ������ � ������ �� ���
				int monsterPositionX = (*monsters[i]).getPosition()[0];
				int monsterPositionY = (*monsters[i]).getPosition()[1];
				ivec2 nextMonsterLocation = ivec2(monsterPositionX + moveDirectionToVector[direction].x,
					monsterPositionY + moveDirectionToVector[direction].y);
				//������� ���� ���� ������
				int nextLocationType = passabilityMap[nextMonsterLocation.x][nextMonsterLocation.y];
				//�������� �� ������� �����������
				if (nextLocationType == 0) {
					(*monsters[i]).move(direction);
					//�������� ����� ������������ ��� �������� ��������
					passabilityMap[monsterPositionX][monsterPositionY] = 0;
					passabilityMap[nextMonsterLocation.x][nextMonsterLocation.y] = 3;
				}
					
			}
		}
	}
}

void randomizeDirection(MoveDirection& direction)
{
	int randomNum = rand() % 5; // ���������� ��������� ����� �� 0 �� 4
	switch (randomNum) {
	case 0:
		direction = MoveDirection::STOP;
		break;
	case 1:
		direction = MoveDirection::LEFT;
		break;
	case 2:
		direction = MoveDirection::RIGHT;
		break;
	case 3:
		direction = MoveDirection::UP;
		break;
	case 4:
		direction = MoveDirection::DOWN;
		break;
	}
}

void cameraSimulation(float simulationTime) {
	float currentSpeedHorizontal = speedHorizontal * simulationTime / 1000;
	float currentSpeedVertical = speedVertical * simulationTime / 1000;
	float currentSpeedZoom = speedZoom * simulationTime / 1000;

	if (GetAsyncKeyState(VK_RIGHT))
	{
		camera.rotateLeftRight(-currentSpeedHorizontal);
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		camera.rotateLeftRight(currentSpeedHorizontal);
	}
	if (GetAsyncKeyState(VK_UP))
	{
		camera.rotateUpDown(currentSpeedVertical);
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		camera.rotateUpDown(-currentSpeedVertical);
	}
	if (GetAsyncKeyState(VK_ADD))
	{
		camera.zoomInOut(currentSpeedZoom);
	}
	if (GetAsyncKeyState(VK_SUBTRACT))
	{
		camera.zoomInOut(-currentSpeedZoom);
	}
}

void gameObjectSimulation(float simulationTime)
{	
	if(player != nullptr) (*player).simulate(simulationTime);
	for (int i = 0; i < 3; i++) (*monsters[i]).simulate(simulationTime);
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			if (passabilityMap[i][j] == 1) (*mapObjects[i][j]).simulate(simulationTime);
		}
	}
}

void setWindowFPS() {
	//��������� ���
	summ += simTime;
	if (summ >= 1000) {
		summ -= 1000;
		int currentFPS = getFPS();
		glutSetWindowTitle(("fps: " + to_string(currentFPS)).c_str());
	}
}
