#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
//////////////// 0 = 빈공간/□  1 = 눈/● 
//         - - - - -
//        |         |
//        |   위 | 
//        |         |
// - - - - ~  ~ ~ ~  - - - - - - - -
//|       :         :        :        |
//| 정면  :    2    :  3     :    4   |   정면에서 보는 면 = 1
//|  = 1  :         :        :        |   정면에서 보는 면 좌측이 2, 우측이 4
// - - - -  ~ ~ ~ ~  - - - - - - - - 
//        |         |
//        |    밑   | 
//        |         |
//         - - - - -
int arr[10][10][10] = { 0 };//맵, arr[높이][세로][가로]
int Time;//시간 설정할 변수
double interval;//간격 설정할 변수
int now = 1;//현재출력하는 면
int snow1, snow2, snow3;
int key;//키보드 입력
int move = 0;//생성된 눈의 갯수를 알려줄 변수
void Snow();//눈생성 
void Scanf();//입력할 함수
void PrintMap();
void SnowMove();//눈 내려가는 함수
void Key();//스페이스 & 좌 &우
int main(void)
{
	srand(time(NULL));
	int stop = 0;
	while (stop == 0) {
		system("cls");
		Scanf();
		Snow();
		PrintMap();
		SnowMove();
		Key();
	}
}
void PrintMap()
{
	int i, j, k;//높이 세로 가로
	int count = 0;
	double interval2 = 0;
	interval2 = interval * 1000;
	Sleep(interval2);
	system("cls");
	printf("--------------------위에서 본 모습----------------------\n");//높이 & 가로
	for (i = 9; i >= 0; i--)//높이
	{
		for (k = 0; k < 10; k++)//가로
		{
			for (j = 0; j < 10; j++)
			{
				if (arr[i][j][k] == 1)//배열공간에 1이 들어가있을때 그 갯수 세기
				{
					count += 1;
				}
			}
			if (count > 0) {
				printf("●");
			}
			else
			{
				printf("  ");
			}
			count = 0;
		}
		printf("\n");
	}///////////////////////////////////////위에서 본 면 출력
	if (now == 1)
	{
		printf("-------------------1번면 출력 ------------------------\n");//세로 & 가로
		for (j = 0; j < 10; j++)//세로
		{
			for (k = 0; k < 10; k++)//가로
			{
				for (i = 0; i < 10; i++)
				{
					if (arr[i][j][k] == 1)//배열공간에 1이 들어가있을때 그 갯수 세기
					{
						count += 1;
					}
				}
				if (count > 0) {
					printf("●");
				}
				else
				{
					printf("  ");
				}
				count = 0;
			}
			printf("\n");
		}
	}/////////////////////////////1번면 출력
	else if (now == 2) {
		printf("-------------------2번면 출력 ------------------------\n");//세로 & 높이
		for (j = 0; j < 10; j++)//세로
		{
			for (i = 9; i >= 0; i--)//높이
			{
				for (k = 0; k < 10; k++) {
					if (arr[i][j][k] == 1)//배열공간에 1이 들어가있을때 그 갯수 세기
					{
						count += 1;
					}
				}
				if (count > 0) {
					printf("♥");
				}
				else
				{
					printf("  ");
				}
				count = 0;
			}
			printf("\n");
		}
	}///////////////////////////////////2면 출력
	else if (now == 3)
	{
		printf("--------------------3번면 출력 ------------------------\n");
		for (j = 0; j < 10; j++)//세로
		{
			for (k = 9; k >= 0; k--)//가로
			{
				for (i = 0; i < 10; i++)
				{
					if (arr[i][j][k] == 1)//배열공간에 1이 들어가있을때 그 갯수 세기
					{
						count += 1;
					}
				}
				if (count > 0) {
					printf("※");
				}
				else
				{
					printf("  ");
				}
				count = 0;
			}
			printf("\n");
		}
	}////////////////////////3면 출력
	else if (now == 4)
	{
		printf("-------------------------4번면 출력 -------------------------\n");
		for (j = 0; j < 10; j++)//세로
		{
			for (i = 0; i < 10; i++)//높이
			{
				for (k = 0; k < 10; k++)
				{
					if (arr[i][j][k] == 1)//배열공간에 1이 들어가있을때 그 갯수 세기
					{
						count += 1;
					}
				}
				if (count > 0) {
					printf("＠");
				}
				else
				{
					printf("□");
				}
				count = 0;
			}
			printf("\n");
		}
	}
}
void Scanf()
{
	printf("눈 내리는 시간 설정: ");
	scanf_s("%d", &Time);
	printf("\n");
	printf("눈 내리는 간격 설정: ");
	scanf_s("%lf", &interval);
	printf("\n");
}
void Snow()
{
	int num = 0;
	move += 6;
	while (num < 6)
	{
		snow1 = rand() % 10;
		snow3 = rand() % 10;
		snow2 = 0;
		if (arr[snow1][snow2][snow3] == 0) {
			arr[snow1][snow2][snow3] = 1;
			num += 1;
		}
	}
}
void SnowMove()
{
	int i, j, k;
	int move2 = 0;//움직인 눈의 갯수를 알려줄 변수
	int newmove = 0;//눈이 새로 생기려고 기존에 몇개의 눈이 세로4인지 알려주는 변수
	double interval3 = 0;
	while (Time > interval3)//조건 고치기
	{
		for (i = 9; i >= 0; i--)//세로
		{
			for (j = 0; j < 10; j++)//높이
			{
				for (k = 0; k < 10; k++)//가로
				{
					if (i == 1 & arr[j][i][k] == 1)
					{
						arr[j][i][k] = 0;
						arr[j][i + 1][k] = 1;
						newmove += 1;
						move2 += 1;//눈이 움직인 횟수 알아주기
					}
					else if (arr[j][i][k] == 1) {
						if (i == 9) {
							arr[j][i][k] = 0;
							move -= 1;
						}
						else {
							arr[j][i][k] = 0;
							arr[j][i + 1][k] = 1;
							move2 += 1;//눈이 움직인 횟수 알아주기
						}
					}
				}
				if (move == move2) {
					i = -1;
					j = 10;//그만 움직이게 하기
				}
				if (newmove == 6)
				{
					Snow();
					newmove = 0;
				}
			}
		}
		interval3 += interval;
		PrintMap();
		move2 = 0;
	}
}
void Key()
{
	int stop = 0;
	int i, j, k;
	printf("키보드 입력하세요.\n");
	while (stop == 0) {//스페이스바 누르면 탈출
		key = getch();
		if (key == 224) {
			key = getch();
		}
		if (key == 75)//좌
		{
			if (now == 4)
			{
				now = 1;
			}
			else
			{
				now += 1;
			}
		}
		else if (key == 77)//우
		{
			if (now == 1)
			{
				now = 4;
			}
			else
			{
				now -= 1;
			}
		}
		PrintMap();
		if (key == 32)
		{
			move = 0;
			now = 1;
			for (i = 0; i < 10; i++)
			{
				for (j = 0; j < 10; j++)
				{
					for (k = 0; k < 10; k++)
					{
						arr[i][j][k] = 0;
					}
				}
			}
			stop += 1;
		}
	}
}
