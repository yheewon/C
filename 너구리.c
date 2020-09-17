#include <windows.h>
#include <stdio.h>
#include <process.h>
#include<stdlib.h>
#include<time.h>
//1=길 2=벽 3=게이머●  4=컴퓨터♡ 5=사과 ★
int arr[5][10] = {
	{ 1,1,1,1,1,1,1,1,1,1 },
	{ 1,2,2,2,2,1,2,2,2,1 },
	{ 1,1,1,1,1,1,1,1,1,1 },
	{ 1,2,2,2,2,1,2,2,2,1 },
	{ 1,1,1,1,1,1,1,1,1,1 }, };//맵
int gx, gy, c0, c1, c2;//게이머 위치/컴퓨터 y좌표
int key;
int Applenum = 0,count=0;//사과 총개수,현재 먹은 사과 개수
int Break = 0;//쓰레드 끝내기
unsigned __stdcall  Gamer() {//게이머 움직이기
 //72:상 75:좌 77우 80하
	while (Break == 0 || count!=Applenum) {
		key = getch();
		if (key == 72) {//위로
			if (arr[gx - 1][gy] != 2) {
				if (arr[gx - 1][gy] == 4) {//컴퓨터랑 만났을때
					arr[gx][gy] = 1;
					gx -= 1;
					arr[gx][gy] = 4;
					Break=1;
				}
				if (arr[gx - 1][gy] == 5) {//가려는 곳이 사과
					count++;
				}
				arr[gx][gy] = 1;
				gx -= 1;
				arr[gx][gy] = 3;
			}
		}
		else if (key == 75) {//왼쪽
			if (arr[gx][gy - 1] != 2) {
				if (arr[gx][gy - 1] == 4) {//컴퓨터랑 만났을때
					arr[gx][gy] = 1;
					gy -= 1;
					arr[gx][gy] = 4;
					Break=1;
				}
				if (arr[gx][gy - 1] == 5) {//가려는 곳이 사과
					count++;
				}
				arr[gx][gy] = 1;
				gy -= 1;
				arr[gx][gy] = 3;
			}
		}
		else if (key == 77) {//오른쪽
			if (arr[gx][gy + 1] != 2) {
				if (arr[gx][gy + 1] == 4) {//컴퓨터랑 만났을때
					arr[gx][gy] = 1;
					gy += 1;
					arr[gx][gy] = 4;
					Break=1;
				}
				if (arr[gx][gy + 1] == 5) {//가려는 곳이 사과
					count++;
				}
				arr[gx][gy] = 1;
				gy += 1;
				arr[gx][gy] = 3;
			}
		}
		else if (key == 80) {//밑으로
			if (arr[gx + 1][gy] != 2) {
				if (arr[gx + 1][gy] == 4) {//컴퓨터랑 만났을때
					arr[gx][gy] = 1;
					gx += 1;
					arr[gx][gy] = 4;
					Break=1;
				}
				if (arr[gx + 1][gy] == 5) {//가려는 곳이 사과
					count++;
				}
				arr[gx][gy] = 1;
				gx += 1;
				arr[gx][gy] = 3;
			}
		}
	}
	return 0;
}
unsigned __stdcall  Print() {
	while (Break == 0) {
		system("cls");
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (arr[i][j] == 1)//길
				{
					printf("□");
				}
				else if (arr[i][j] == 2)//벽
				{
					printf("■");
				}
				else if (arr[i][j] == 3)//게이머
				{
					printf("●");
				}
				else if (arr[i][j] == 4) {//컴퓨터
					printf("♡");
				}
				else if (arr[i][j] == 5) {//사과
					printf("★");
				}
			}
			printf("\n");
		}
	}
	return 0;
}
//unsigned __stdcall  Copmuter1() {//0번째 컴퓨터
//	int ad = 0;//컴퓨터가 사과를 지나쳤는지 알려줄 변수
//	if (c0 == 9) {//컴퓨터가 제일 오른쪽에 위치해 있을때
//		if (ad > 0) {//컴퓨터가 사과 밟은적 있음
//			arr[0][c0] = 5;
//			c0=0;
//			ad--;
//			arr[0][c0] = 4;
//		}
//		else {
//			arr[0][c0] = 1;
//			c0 = 0;
//			if (arr[0][c0] == 5) {//사과가있는 경우
//				ad++;
//			}
//			arr[0][c0] = 4;
//		}
//	}
//	else {
//		if (ad > 0) {//컴퓨터가 사과 밟은적 있음
//			arr[0][c0] = 5;
//			c0++;
//			ad--;
//			arr[0][c0] = 4;
//		}
//		else {
//			arr[0][c0] = 1;
//			c0++;
//			if (arr[0][c0] == 5) {//사과가 있는 경우
//				ad++;
//			}
//			arr[0][c0] = 4;
//		}
//	}
//}
void Apple()//사과 입력
{
	srand(time(NULL));
	int a;//확률 입력
	int x, y, stop = 0, stop1 = 0;
	while (stop == 0) {
		x = rand() % 5;
		y = rand() % 10;
		if (arr[x][y] == 1) {//길인 경우
			arr[x][y] = 3;//게이머
			gx = x, gy = y;
			stop = 1;
		}
	}//사용자 위치 정하기
	for (int i = 0; i < 3; i++) {
		while (stop1 == 0) {
			y = rand() % 10;
			if (arr[2 * i][y] == 1) {//길인 경우
				arr[2 * i][y] = 4;//컴퓨터
				if (i == 0)
					c0 = y;
				else if (i == 1)
					c1 = y;
				else if (i == 2)
					c2 = y;
				stop1 = 1;
			}
		}
		stop1 = 0;
	}//컴퓨터 위치 정하기
	printf(" 각 셀에 사과가 놓일 확률: ");
	scanf_s("%d", &a);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			if (arr[i][j] == 1) {//길인 경우
				arr[i][j] = (rand() % 100) + 1;
				if (arr[i][j] <= a) {
					arr[i][j] = 5;//사과
				}
				else {
					arr[i][j] = 1;
				}
			}
		}
	}
	for (int i = 0; i < 5; i++) {//총 사과 개수 세기
		for (int j = 0; j < 10; j++) {
			if (arr[i][j] == 5) {
				Applenum++;
			}
		}
	}
}
int main()
{
	Apple();
	_beginthreadex(NULL, 0, Gamer, 0, 0, NULL);
	_beginthreadex(NULL, 0, Print, 0, 0, NULL);
	while (Break==0 ) {

	}
	printf("-------------------");
}
