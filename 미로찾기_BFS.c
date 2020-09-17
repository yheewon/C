#include <stdio.h>
#include <Windows.h>

int map[16][16] = {//0=빈공간 1=목적지 3=벽 지나온공간:음수로 표시
	{ 0,0,0,0,3,0,0,0,0,0,0,0,3,0,0,0 },
	{ 0,3,3,0,3,0,3,3,3,3,3,0,3,0,3,0 },
	{ 0,0,3,0,0,0,0,0,0,0,3,0,3,0,3,3 },
	{ 3,0,3,3,3,3,3,3,3,0,3,0,0,0,3,0 },
	{ 0,0,0,0,0,0,0,3,0,0,3,3,3,0,3,0 },
	{ 3,0,3,3,3,3,0,3,3,3,3,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3 },
	{ 0,3,3,3,0,3,3,3,3,0,0,3,0,0,0,3 },
	{ 0,0,0,0,0,0,0,0,3,3,3,3,0,3,0,0 },
	{ 3,3,0,3,3,3,3,0,0,3,0,3,0,3,3,0 },
	{ 0,0,0,3,0,3,3,3,0,0,0,3,0,3,0,0 },
	{ 0,3,3,3,0,0,0,3,3,3,3,3,0,3,0,3 },
	{ 0,3,0,0,0,3,0,0,3,0,3,3,0,3,0,3 },
	{ 0,0,0,3,3,3,3,0,3,0,0,0,0,3,0,0 },
	{ 3,0,3,3,0,0,3,0,3,3,3,0,3,3,3,0 },
	{ 0,0,0,0,0,3,3,0,0,0,0,0,0,0,3,0 }
};

int user_x = 0, user_y = 0;//사용자 위치
int front = 0;//큐 배열속 처음
int rear = -1;//큐 배열속 마지막
int x[100], y[100];//큐

void PrintMap_Num();//숫자로 맵출력
void Move();
int Add();
void Delete();
void PrintPath();

int main(void) {
	PrintMap_Num();

	Move();
	printf("\n최단거리 탐색 완료\n");
	PrintPath() 

}

void PrintMap_Num() {
	Sleep(50);
	system("cls");
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			if (i == 15 && j == 15) printf("  ★");
			else if (map[i][j] < 0) printf(" %d", map[i][j]);
			else if (map[i][j] == 3) printf("  ■");
			else printf("  %d ", map[i][j]);
		}
		printf("\n");
	}

	printf("rear: %d", rear);
	printf("   front: %d\n", front);

}

int Add(num1, num2) {
	rear++;
	x[rear] = num2;
	y[rear] = num1;
}

void Delete() {
	user_x = x[front];
	user_y = y[front];
	front++;
}

void Move() {
	Add(0, 0);
	PrintMap_Num();
	map[user_y][user_x] = -1;//방문 위치 표시

	while (1) {
		Delete();//큐에서 위치 빼오기

		if (user_y == 15 && user_x == 15) break;
		else {//지나갈수 있는길 : 0 또는 1
			if (map[user_y - 1][user_x] == 0 && user_y > 0) {//북
				Add(user_y - 1, user_x);//큐 삽입
				map[user_y - 1][user_x] = map[user_y][user_x] - 1;//방문위치 표시
			}
			if (map[user_y][user_x + 1] == 0 && user_x < 15) {//동
				Add(user_y, user_x + 1);//큐 삽입
				map[user_y][user_x + 1] = map[user_y][user_x] - 1;//방문위치 표시

			}
			if (map[user_y + 1][user_x] == 0 && user_y < 15) {//남
				Add(user_y + 1, user_x);//큐 삽입
				map[user_y + 1][user_x] = map[user_y][user_x] - 1;//방문위치 표시

			}
			if (map[user_y][user_x - 1] == 0 && user_x > 0) {//서
				Add(user_y, user_x - 1);//큐 삽입
				map[user_y][user_x - 1] = map[user_y][user_x] - 1;//방문위치 표시
			}
		}

		PrintMap_Num();
	}

}

void PrintPath() {
	int position = map[15][15] + 1;
	int x = 15, y = 15;
	map[x][y] = 100;

	while (position != 0) {
		if (map[y - 1][x] == position) {//북
			position++;
			y--;
			map[y][x] = 100;
		}
		if (map[y][x + 1] == position) {//동
			x++;
			map[y][x] = 100;
			position++;
		}
		if (map[y + 1][x] == position&& y < 15) {//남
			y++;
			map[y][x] = 100;
			position++;
		}
		if (map[y][x - 1] == position&&x > 0) {//서
			x--;
			map[y][x] = 100;
			position++;
		}
	}

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			if (map[i][j] == 100) printf("□");
			else if (map[i][j] == 3) printf("■");
			else printf("  ");
		}
		printf("\n");
	}
	printf("끝!!!!!!!!!!!");
}
