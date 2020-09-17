#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<Windows.h>
#include<ctime>
using namespace std;
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
// 0 = 빈공간, 1= 눈 2 = 트리 
class Snow {
private:
	int arr[10][10][10]; //arr[높이][세로][가로]
	int now = 0;//현재 보이는 면
	int sleep = 0;
public:
	void Init_String();//삼차원 배열 초기화
	void Print();//맵 출력
	void Select_tree();//나무 위치 정하기
	void snow();//눈위치
	void Snow_move(int n);//눈 내리기
	void key();//정면 돌리기
};
Snow a;
void Snow::Init_String() {//삼차원 배열 초기화
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			for (int h = 0; h < 10; h++) {
				arr[i][j][h] = 0;
			}
		}
	}
	arr[0][0][0] = 2;//나무 자랄 시작점
	a.Print();
}
void Snow::Print() {
	if (sleep == 1)
		Sleep(500);
	system("cls");
	int count = 0, c8 = 0, c9 = 0, c7 = 0;
	int i, j = 0, k, s = 0;
	cout << "--------------------위에서 본 모습----------------------" << endl;//높이 & 가로
	for (i = 9; i >= 0; i--)//높이
	{
		for (k = 0; k < 10; k++)//가로
		{
			j = 0;
			while (s == 0 && j <= 9) {
				if (arr[i][j][k] == 1 || arr[i][j][k] == 2) {//배열공간이 눈이거나 트리 위치좌표
					count += 1;
				}
				else if (arr[i][j][k] == 8) {
					c8 += 1;
					s = 1;
				}
				else if (arr[i][j][k] == 9) {
					c9 += 1;
					s = 1;
				}
				else if (arr[i][j][k] == 7) {
					c7 += 1;
					s = 1;
				}
				j++;
			}
			if (count > 0)
				cout << "●";
			else if (c8 > 0)
				cout << "♡";
			else if (c9 > 0)
				cout << "♤";
			else if (c7 > 0)
				cout << "☆";
			else
				cout << "□";
			count = 0, c8 = 0, c9 = 0, c7 = 0, s = 0;
		}
		cout << endl;
	}///////////////////////////////////////위에서 본 면 출력
	if (now == 1)
	{
		cout << "--------------------1번면(정면)----------------------" << endl;//세로 & 가로
		for (j = 0; j < 10; j++)//세로
		{
			for (k = 0; k < 10; k++)//가로
			{
				i = 0;
				while (s == 0 && i <= 9) {
					if (arr[i][j][k] == 1 || arr[i][j][k] == 2) {//배열공간이 눈이거나 트리 위치좌표
						count += 1;
					}
					else if (arr[i][j][k] == 8) {
						c8 += 1;
						s = 1;
					}
					else if (arr[i][j][k] == 9) {
						c9 += 1;
						s = 1;
					}
					else if (arr[i][j][k] == 7) {
						c7 += 1;
						s = 1;
					}
					i++;
				}
				if (count > 0)
					cout << "●";
				else if (c8 > 0)
					cout << "♡";
				else if (c9 > 0)
					cout << "♤";
				else if (c7 > 0)
					cout << "☆";
				else
					cout << "□";
				count = 0, c8 = 0, c9 = 0, c7 = 0, s = 0;
			}
			cout << endl;
		}
	}/////////////////////////////1번면 출력
	else if (now == 2) {
		cout << "--------------------2번면(정면 왼쪽)----------------------" << endl;//세로 & 높이
		for (j = 0; j < 10; j++)//세로
		{
			for (i = 9; i >= 0; i--)//높이
			{
				k = 0;
				while (s == 0 && k <= 9) {
					if (arr[i][j][k] == 1 || arr[i][j][k] == 2) {//배열공간이 눈이거나 트리 위치좌표
						count += 1;
					}
					else if (arr[i][j][k] == 8) {
						c8 += 1;
						s = 1;
					}
					else if (arr[i][j][k] == 9) {
						c9 += 1;
						s = 1;
					}
					else if (arr[i][j][k] == 7) {
						c7 += 1;
						s = 1;
					}
					k++;
				}
				if (count > 0)
					cout << "●";
				else if (c8 > 0)
					cout << "♡";
				else if (c9 > 0)
					cout << "♤";
				else if (c7 > 0)
					cout << "☆";
				else
					cout << "□";
				count = 0, c8 = 0, c9 = 0, c7 = 0, s = 0;
			}
			cout << endl;
		}
	}///////////////////////////////////2면 출력
	else if (now == 3)
	{
		cout << "--------------------3번면(정면 맞은편)----------------------" << endl;//세로 & 높이
		for (j = 0; j < 10; j++)//세로
		{
			for (k = 9; k >= 0; k--)//가로
			{
				i = 9;
				while (s == 0 && i >= 1) {
					if (arr[i][j][k] == 1 || arr[i][j][k] == 2) {//배열공간이 눈이거나 트리 위치좌표
						count += 1;
					}
					else if (arr[i][j][k] == 8) {
						c8 += 1;
						s = 1;
					}
					else if (arr[i][j][k] == 9) {
						c9 += 1;
						s = 1;
					}
					else if (arr[i][j][k] == 7) {
						c7 += 1;
						s = 1;
					}
					i--;
				}
				if (count > 0)
					cout << "●";
				else if (c8 > 0)
					cout << "♡";
				else if (c9 > 0)
					cout << "♤";
				else if (c7 > 0)
					cout << "☆";
				else
					cout << "□";
				count = 0, c8 = 0, c9 = 0, c7 = 0, s = 0;
			}
			cout << endl;
		}
	}////////////////////////3면 출력
	else if (now == 4)
	{
		cout << "--------------------4번면(정면 오른쪽)----------------------" << endl;
		for (j = 0; j < 10; j++)//세로
		{
			for (i = 0; i < 10; i++)//높이
			{
				k = 9;
				while (s == 0 && k >= 1) {
					if (arr[i][j][k] == 1 || arr[i][j][k] == 2) {//배열공간이 눈이거나 트리 위치좌표
						count += 1;
					}
					else if (arr[i][j][k] == 8) {
						c8 += 1;
						s = 1;
					}
					else if (arr[i][j][k] == 9) {
						c9 += 1;
						s = 1;
					}
					else if (arr[i][j][k] == 7) {
						c7 += 1;
						s = 1;
					}
					k--;
				}
				if (count > 0)
					cout << "●";
				else if (c8 > 0)
					cout << "♡";
				else if (c9 > 0)
					cout << "♤";
				else if (c7 > 0)
					cout << "☆";
				else
					cout << "□";
				count = 0, c8 = 0, c9 = 0, c7 = 0, s = 0;
			}
			cout << endl;
		}
	}
}
void Snow::Select_tree() {
	cout << "\n원하는 위치에 도착하면 스페이스 키 누르세요" << endl;
	cout << "윗면에서 높이 선택 - 상 하 만 움직일수 있습니다. " << endl;
	int stop1 = 0, stop2 = 0, i = 0, j = 0, k = 0;
	while (stop1 == 0) {
		//72:상 75:좌 77우 80하
		int key = getch();
		if (key == 72) {//상
			arr[i][0][0] = 0;
			i++;
			arr[i][0][0] = 2;
		}
		else if (key == 80) {//하
			arr[i][0][0] = 0;
			i--;
			arr[i][0][0] = 2;
		}
		else if (key == 32) {
			stop1 = 1;
		}
		a.Print();
		cout << "윗면에서 높이 선택 - 상 하 만 움직일수 있습니다. " << endl;
	}
	now = 1;
	a.Print();
	while (stop2 == 0) {
		int key = getch();
		if (key == 72) {//상
			arr[i][j][k] = 0;
			j--;
			arr[i][j][k] = 2;
		}
		else if (key == 75) {//좌
			arr[i][j][k] = 0;
			k--;
			arr[i][j][k] = 2;
		}
		else if (key == 77) {//우
			arr[i][j][k] = 0;
			k++;
			arr[i][j][k] = 2;
		}
		else if (key == 80) {//하
			arr[i][j][k] = 0;
			j++;
			arr[i][j][k] = 2;
		}
		else if (key == 32)
			stop2 = 1;
		a.Print();
	}//나무 위치 설정 완료
	arr[i][j][k] = 7;
	cout << "나무 위치 설정 완료" << endl;
	int high = rand() % 3 + 2;//나무 높이 랜덤으로 설정
	j = j - high + 1;
	for (int h = 0; h < high; h++) {
		for (int q = i - h; q <= i + h; q++) {
			for (int g = k - h; g <= k + h; g++) {
				arr[q][j + h][g] = rand() % 3 + 7;
				cout << arr[q][j + h][g];
			}
		}
	}
	a.Print();
}
void Snow::snow() {
	int s1, s2;
	for (int i = 0; i < 8; i++) {
		s1 = rand() % 10;
		s2 = rand() % 10;
		if (arr[s1][0][s2] == 0)
			arr[s1][0][s2] = 1;
	}
}
void Snow::Snow_move(int n) {
	double stop = 0;
	int temp, cou = 0;
	sleep = 1;
	a.Print();
	while (n > stop) {
		if (cou % 2 == 0)
			a.snow();
		for (int i = 9; i >= 0; i--) {//세로
			for (int j = 0; j < 10; j++) {//높이
				for (int k = 0; k < 10; k++) {//가로
					if (arr[j][i][k] == 1) {
						if (i == 9)
							arr[j][i][k] = 0;
						else {
							arr[j][i][k] = 0;
							if (arr[j][i + 1][k] != 0) {//가려는곳이 빈공간이 아님
								temp = arr[j][i + 1][k];
								arr[j][i + 1][k] = temp;
							}
							else
								arr[j][i + 1][k] = 1;
						}
					}
				}
			}
		}
		stop += 0.5;
		a.Print();
		cou++;
	}
}
void Snow::key() {
	int stop = 0;
	int i, j, k;
	sleep = 0;
	printf("키보드 입력하세요.\n");
	while (stop == 0) {
		int key = getch();
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

		a.Print();
	}
}
int main() {
	srand(time(NULL));
	int Time;//눈 내릴 시간
	cout << "눈 내릴 시간 입력 : ";
	cin >> Time;
	a.Init_String();
	a.Select_tree();
	int key;
	key = getch();
	if (key == 32)
		a.snow();
	a.Snow_move(Time);
	a.key();
}
