#include <stdio.h>
#include <Windows.h>

int map[16][16] = {//0=빈공간 1=목적지 2=지나온 공간 3=벽
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
	{ 0,0,0,0,0,3,3,0,0,0,0,0,0,0,3,1 }
};

int user_x = 0, user_y = 0;
int x[100], y[100], top = 0;
void PrintMap();
void Push();
void Move();
int User_Move();
void Pop();

int main(void) {
	PrintMap();//맵출력
	
	Move();

	printf("\n끄으으으으으으읕\n");
}

void PrintMap() {
	Sleep(50);
	system("cls");

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			if (user_y == i && user_x == j)
			{
				printf("★");
			}
			else if (map[i][j] == 1) printf("♥");
			else if (map[i][j] < 3)
			{
				printf("　");
			}
			else if (map[i][j] == 3)
			{
				printf("■");
			}
		}
		printf("\n");
	}
}

void Push() {
	x[top] = user_x;
	y[top] = user_y;
	top++;
}

void Pop() {
	top--;
	user_x = x[top];
	user_y = y[top];
}

void Move() {
	while (1) {
		int move;
		move=User_move();

		if (move == 0) {//종료
			break;
		}
		else if (move == 1) {//막다른길
			Pop();
		}
		PrintMap();
	}

}
int User_move() {
	int count = 0;
	if (map[user_y][user_x] == 1) return 0;//목적지 도착
	else {
		map[user_y][user_x] = 2;//지나온 공간 표시하기
		if (map[user_y - 1][user_x] < 2 && user_y>0) {//북
			Push();//움직이기 전 위치 스택에 넣기
			user_y--;
			count++;
		}
		else if (map[user_y][user_x + 1] < 2 && user_x<15) {//동
			Push();//움직이기 전 위치 스택에 넣기
			user_x++;
			count++;
		}
		else if (map[user_y + 1][user_x] < 2 && user_y<15) {//남
			Push();//움직이기 전 위치 스택에 넣기
			user_y++;
			count++;
		}
		else if (map[user_y][user_x - 1] < 2 && user_x>0) {//서
			Push();//움직이기 전 위치 스택에 넣기
			user_x--;
			count++;
		}
	}

	if (count == 0) return 1;//막다른길 도착
	else return 2;//사용자 움직임
}
