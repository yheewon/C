#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
typedef struct StartArray {
	int decimal;// 10진수
	int b1, b2, b3, b4;//binary2진수 
	int one;//1의 개수
}start;
typedef struct GroupArray {//그룹화 시킨후
	int deimal;
	int b1, b2, b3, b4;
}group;
typedef struct Changing_bit1 {//머징 1단계
	int merging[2];
	int binary[4];
}first;
typedef struct Changing_bit2 {//머징 2단계
	int merging[4];
	int binary[4];
}second;
typedef struct Changing_bit3 {//머징 3단계
	int merging[8];
	int binary[4];
}third;
typedef struct Changing_bit4 {//머징 4단계
	int merging[16];
	char binary[4];
}fourth;
typedef struct Prime_implicants {//P.I 
	int binary[4];
	int merging[16];
	int merging_num;//( , )괄호 안에 있는 숫자 개수
}prime;
typedef struct Chart {//표안에 x표시 해줄 구조체
	int x[16];
}chart;
typedef struct Essential_PI {
	int binary[4];
	int merging[16];
	int merging_num;
	int pi_order;//pi내에서의 순서
}essential;
start input[50];
group array[50];
first m1[50];
second m2[50];
third m3[50];
fourth m4[5];
prime pi[20];
chart c[20];
essential epi[10];
int a;//숫자 입력 받을 배열
int num;//숫자 갯수
int key;//스페이스
int order = 0;//구조체 input배열 순서(Change 함수)
int c0 = 0, c1 = 0, c2 = 0, c3 = 0, c4 = 0;//그룹으로 묶고 난후에 각 그룹마다 몇개들어있는지 알려주는 함수
int first0 = 0, first1 = 0, first2 = 0, first3 = 0;//처음 머징하고 단계마다 몇개들어있는지 알려주는 함수
int second0 = 0, second1 = 0, second2 = 0;//두번째 머징하고 단계마다 몇개 들어있는지 알려주는 함수
int third0 = 0; third1 = 0;// 세번째 머징하고 단계마다 몇개 들어있는지 알려주는 함수
int Fir_result;//첫번재 머징이후 몇개의 결과값
int Sec_result;//두번째머징이후 몇개의 결과값
int Third = 0;//현재까지 몇번의 마징이 이뤄졌는지 체크해줄 변수
int pnumber = 0;//pi순서
void Change();//십진수 이진수로 변환시키는 함수
void Change_Print();//이진수로 변환한값 출력해주는 함수
void Group();//1의개수로 그룹화 시킬 함수
void First_Merging();//머징할 함수
void Second_Merging();//두번째 머징
void Third_Merging();//세번재 머징
void Fourth_Merging();//네번째 머징
void Search_pi();//p.i 찾기
void Search_epi();//epi찾기
int main(void)
{
	int i;
	printf("입력할 숫자 갯수: ");
	scanf_s("%d", &num);
	for (i = 0; i < num; i++) {
		scanf_s("%d", &a);
		Change();//십진수 이진수로 변환시키는 함수
	}//이진수 변환 끝
	key = getch();
	if (key == 32) {
		Change_Print();
	}
	Group();//1의개수로 그룹화 시킬 함수
	First_Merging();//머징할 함수
	Second_Merging();//두번째 머징
	Third_Merging();//세번재 머징
	if (num == 16) {
		Fourth_Merging();
	}
	Search_pi();//pi 찾기
	Search_epi();
}
void Change()//십진수 이진수로 변환시키는 함수
{
	int number = 0;//rset 배열 순서
	int rest[4] = { 0 };//십진수 2로 나눈 나머지들 저장할 배열
	input[order].decimal = a;
	for (int j = 0; a > 0; j++) {
		rest[number] = a % 2;
		a = a / 2;
		number += 1;
	}//십진수 2 나머지 rest배열에 넣어주기
	input[order].b1 = rest[3];
	input[order].b2 = rest[2];
	input[order].b3 = rest[1];
	input[order].b4 = rest[0];//rest 배열에 있는 값들 거꾸로 구조체 이진수 변수에 넣어주기
	order++;
	number = 0;
	for (int j = 0; j < 4; j++)
	{
		rest[j] = 0;
	}//rest배열 초기화
}
void Change_Print()//이진수로 변환한값 출력해주는 함수
{
	system("cls");
	printf("십진수 --------------> 이진수\n\n");
	for (int i = 0; i < num; i++) {
		printf("  %d    --------------> %d%d%d%d\n", input[i].decimal, input[i].b1, input[i].b2, input[i].b3, input[i].b4);
	}
}
void Group()//1의개수로 그룹화 시킬 함수
{
	int count = 0;//1의 개수 카운트
	int anumber = 0;//array순서
	for (int i = 0; i < num; i++) {
		if (input[i].b1 == 1) {
			count++;
		}
		if (input[i].b2 == 1) {
			count++;
		}
		if (input[i].b3 == 1) {
			count++;
		}
		if (input[i].b4 == 1) {
			count++;
		}
		input[i].one = count;//각 이진수 1의 개수 세기
		if (count == 0) {
			c0++;
		}
		else if (count == 1) {
			c1++;
		}
		else if (count == 2) {
			c2++;
		}
		else if (count == 3) {
			c3++;
		}
		else if (count == 4) {
			c4++;
		}
		count = 0;
	}
	key = getch();
	if (key == 32) {
		system("cls");
		printf(" 그룹화\n\n");
		for (int i = 0; i < num; i++) {//input배열 array배열에 복사
			if (input[i].one == 0) {
				array[anumber].deimal = input[i].decimal;
				array[anumber].b1 = input[i].b1;
				array[anumber].b2 = input[i].b2;
				array[anumber].b3 = input[i].b3;
				array[anumber].b4 = input[i].b4;
				printf(" (%d)   --------------> %d%d%d%d\n", array[anumber].deimal, array[anumber].b1, array[anumber].b2, array[anumber].b3, array[anumber].b4);
				anumber++;
			}
		}
		printf("=======================================\n");
		for (int i = 0; i < num; i++) {
			if (input[i].one == 1) {
				array[anumber].deimal = input[i].decimal;
				array[anumber].b1 = input[i].b1;
				array[anumber].b2 = input[i].b2;
				array[anumber].b3 = input[i].b3;
				array[anumber].b4 = input[i].b4;
				printf(" (%d)   --------------> %d%d%d%d\n", array[anumber].deimal, array[anumber].b1, array[anumber].b2, array[anumber].b3, array[anumber].b4);
				anumber++;
			}
		}
		printf("=======================================\n");
		for (int i = 0; i < num; i++) {
			if (input[i].one == 2) {
				array[anumber].deimal = input[i].decimal;
				array[anumber].b1 = input[i].b1;
				array[anumber].b2 = input[i].b2;
				array[anumber].b3 = input[i].b3;
				array[anumber].b4 = input[i].b4;
				printf(" (%d)   --------------> %d%d%d%d\n", array[anumber].deimal, array[anumber].b1, array[anumber].b2, array[anumber].b3, array[anumber].b4);
				anumber++;
			}
		}
		printf("=======================================\n");
		for (int i = 0; i < num; i++) {
			if (input[i].one == 3) {
				array[anumber].deimal = input[i].decimal;
				array[anumber].b1 = input[i].b1;
				array[anumber].b2 = input[i].b2;
				array[anumber].b3 = input[i].b3;
				array[anumber].b4 = input[i].b4;
				printf(" (%d)   --------------> %d%d%d%d\n", array[anumber].deimal, array[anumber].b1, array[anumber].b2, array[anumber].b3, array[anumber].b4);
				anumber++;
			}
		}
		printf("=======================================\n");
		for (int i = 0; i < num; i++) {
			if (input[i].one == 4) {
				array[anumber].deimal = input[i].decimal;
				array[anumber].b1 = input[i].b1;
				array[anumber].b2 = input[i].b2;
				array[anumber].b3 = input[i].b3;
				array[anumber].b4 = input[i].b4;
				printf(" (%d)   --------------> %d%d%d%d\n", array[anumber].deimal, array[anumber].b1, array[anumber].b2, array[anumber].b3, array[anumber].b4);
				anumber++;
			}
		}
	}
}
void First_Merging()//머징할 함수
{
	int count = 0;//머징 조건에 적합한지 찾을 변수
	int mnumber = 0;//m1순서
	int enter = 0;
	if (c0 > 0) {//0단계 존재
		for (int i = 0; i < c0; i++) {
			for (int h = c0; h < c0 + c1; h++) {
				if (array[i].b1 == array[h].b1) {
					count++;
				}
				if (array[i].b2 == array[h].b2) {
					count++;
				}
				if (array[i].b3 == array[h].b3) {
					count++;
				}
				if (array[i].b4 == array[h].b4) {
					count++;
				}
				if (count == 3) {//1개만 다를때 머징
					first0++;
					m1[mnumber].merging[0] = array[i].deimal;
					m1[mnumber].merging[1] = array[h].deimal;
					if (array[i].b1 == array[h].b1) {
						m1[mnumber].binary[0] = array[i].b1;
					}
					else {
						m1[mnumber].binary[0] = 9;//나중에 -로 바꿔서 출력
					}
					if (array[i].b2 == array[h].b2) {
						m1[mnumber].binary[1] = array[i].b2;
					}
					else {
						m1[mnumber].binary[1] = 9;//나중에 -로 바꿔서 출력
					}
					if (array[i].b3 == array[h].b3) {
						m1[mnumber].binary[2] = array[i].b3;
					}
					else {
						m1[mnumber].binary[2] = 9;//나중에 -로 바꿔서 출력
					}
					if (array[i].b4 == array[h].b4) {
						m1[mnumber].binary[3] = array[i].b4;
					}
					else {
						m1[mnumber].binary[3] = 9;//나중에 -로 바꿔서 출력
					}
					mnumber++;
				}
				count = 0;
			}
		}
	}
	if (c1 > 0) {//1단계 존재
		for (int i = c0; i < c0 + c1; i++) {
			for (int h = c0 + c1; h < c0 + c1 + c2; h++) {
				if (array[i].b1 == array[h].b1) {
					count++;
				}
				if (array[i].b2 == array[h].b2) {
					count++;
				}
				if (array[i].b3 == array[h].b3) {
					count++;
				}
				if (array[i].b4 == array[h].b4) {
					count++;
				}
				if (count == 3) {//1개만 다를때 머징
					first1++;
					m1[mnumber].merging[0] = array[i].deimal;
					m1[mnumber].merging[1] = array[h].deimal;
					if (array[i].b1 == array[h].b1) {
						m1[mnumber].binary[0] = array[i].b1;
					}
					else {
						m1[mnumber].binary[0] = 9;//나중에 -로 바꿔서 출력
					}
					if (array[i].b2 == array[h].b2) {
						m1[mnumber].binary[1] = array[i].b2;
					}
					else {
						m1[mnumber].binary[1] = 9;//나중에 -로 바꿔서 출력
					}
					if (array[i].b3 == array[h].b3) {
						m1[mnumber].binary[2] = array[i].b3;
					}
					else {
						m1[mnumber].binary[2] = 9;//나중에 -로 바꿔서 출력
					}
					if (array[i].b4 == array[h].b4) {
						m1[mnumber].binary[3] = array[i].b4;
					}
					else {
						m1[mnumber].binary[3] = 9;//나중에 -로 바꿔서 출력
					}
					mnumber++;
				}
				count = 0;
			}
		}
	}
	if (c2 > 0) {//2단계 존재
		for (int i = c0 + c1; i < c0 + c1 + c2; i++) {
			for (int h = c0 + c1 + c2; h < c0 + c1 + c2 + c3; h++) {
				if (array[i].b1 == array[h].b1) {
					count++;
				}
				if (array[i].b2 == array[h].b2) {
					count++;
				}
				if (array[i].b3 == array[h].b3) {
					count++;
				}
				if (array[i].b4 == array[h].b4) {
					count++;
				}
				if (count == 3) {//1개만 다를때 머징
					first2++;
					m1[mnumber].merging[0] = array[i].deimal;
					m1[mnumber].merging[1] = array[h].deimal;
					if (array[i].b1 == array[h].b1) {
						m1[mnumber].binary[0] = array[i].b1;
					}
					else {
						m1[mnumber].binary[0] = 9;//나중에 -로 바꿔서 출력
					}
					if (array[i].b2 == array[h].b2) {
						m1[mnumber].binary[1] = array[i].b2;
					}
					else {
						m1[mnumber].binary[1] = 9;//나중에 -로 바꿔서 출력
					}
					if (array[i].b3 == array[h].b3) {
						m1[mnumber].binary[2] = array[i].b3;
					}
					else {
						m1[mnumber].binary[2] = 9;//나중에 -로 바꿔서 출력
					}
					if (array[i].b4 == array[h].b4) {
						m1[mnumber].binary[3] = array[i].b4;
					}
					else {
						m1[mnumber].binary[3] = 9;//나중에 -로 바꿔서 출력
					}
					mnumber++;
				}
				count = 0;
			}
		}
	}
	if (c3 > 0) {//3단계 존재
		for (int i = c0 + c1 + c2; i < c0 + c1 + c2 + c3; i++) {
			for (int h = c0 + c1 + c2 + c3; h < c0 + c1 + c2 + c3 + c4; h++) {
				if (array[i].b1 == array[h].b1) {
					count++;
				}
				if (array[i].b2 == array[h].b2) {
					count++;
				}
				if (array[i].b3 == array[h].b3) {
					count++;
				}
				if (array[i].b4 == array[h].b4) {
					count++;
				}
				if (count == 3) {//1개만 다를때 머징
					first3++;
					m1[mnumber].merging[0] = array[i].deimal;
					m1[mnumber].merging[1] = array[h].deimal;
					if (array[i].b1 == array[h].b1) {
						m1[mnumber].binary[0] = array[i].b1;
					}
					else {
						m1[mnumber].binary[0] = 9;//나중에 -로 바꿔서 출력
					}
					if (array[i].b2 == array[h].b2) {
						m1[mnumber].binary[1] = array[i].b2;
					}
					else {
						m1[mnumber].binary[1] = 9;//나중에 -로 바꿔서 출력
					}
					if (array[i].b3 == array[h].b3) {
						m1[mnumber].binary[2] = array[i].b3;
					}
					else {
						m1[mnumber].binary[2] = 9;//나중에 -로 바꿔서 출력
					}
					if (array[i].b4 == array[h].b4) {
						m1[mnumber].binary[3] = array[i].b4;
					}
					else {
						m1[mnumber].binary[3] = 9;//나중에 -로 바꿔서 출력
					}
					mnumber++;
				}
				count = 0;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////////////머징한거 출력
	key = getch();
	if (key == 32) {
		system("cls");
		printf("1차 Merging\n\n");
		for (int i = 0; i < first0 + first1 + first2 + first3; i++) {
			if (enter == first0 || enter == first0 + first1 || enter == first0 + first1 + first2 || enter == first0 + first1 + first2 + first3) {
				printf("=======================================\n");
			}
			printf("(%d , %d)         ", m1[i].merging[0], m1[i].merging[1]);
			for (int j = 0; j < 4; j++) {
				if (m1[i].binary[j] == 9) {
					printf("-");
				}
				else {
					printf("%d", m1[i].binary[j]);
				}
			}
			printf("\n");
			enter++;
		}
	}
	Fir_result = first0 + first1 + first2 + first3;
}
void Second_Merging()//두번째 머징
{
	int count = 0;//머징 조건에 적합한지 찾을 변수
	int mnumber = 0;//m2순서
	int enter = 0;
	int same = 0;//중복체크 해줄 변수
	int Second = 0;//현재까지 몇번의 마징이 이뤄졌는지 체크해줄 변수
	int temp[4] = { 0 };//중복확인하려는 p.i값 잠시 넣어두는 배열
	int cnt = 0;//똑같은 pi의 개수
	if (first0 > 0) {
		for (int i = 0; i < first0; i++) {
			for (int h = first0; h < first0 + first1; h++) {
				for (int k = 0; k < 4; k++) {
					if (m1[i].binary[k] == m1[h].binary[k]) {
						count++;
					}
				}
				if (count == 3) {//1개만 다를때 머징
					if (Second > 0) {
						temp[0] = m1[i].merging[0];
						temp[1] = m1[i].merging[1];
						temp[2] = m1[h].merging[0];
						temp[3] = m1[h].merging[1];
						for (int t = 0; t < Second; t++) {
							for (int e = 0; e < 4; e++) {
								for (int m = 0; m < 4; m++) {
									if (m2[t].merging[e] == temp[m]) {
										same++;
									}
								}
							}
							if (same == 4) {
								cnt++;//cnt에 값이 있으면 중복되는 pi가 있다는것
							}
							same = 0;
						}
					}
					if (cnt == 0) {
						second0++;
						m2[mnumber].merging[0] = m1[i].merging[0];
						m2[mnumber].merging[1] = m1[i].merging[1];
						m2[mnumber].merging[2] = m1[h].merging[0];
						m2[mnumber].merging[3] = m1[h].merging[1];
						for (int p = 0; p < 4; p++) {
							if (m1[i].binary[p] == m1[h].binary[p]) {
								m2[mnumber].binary[p] = m1[i].binary[p];
							}
							else {
								m2[mnumber].binary[p] = 9;//나중에 -로 바꿔서 출력
							}
						}
						mnumber++;
						Second++;
					}
				}
				count = 0;
				cnt = 0;
			}
		}
	}
	if (first1 > 0) {
		for (int i = first0; i < first0 + first1; i++) {
			for (int h = first0 + first1; h < first0 + first1 + first2; h++) {
				for (int k = 0; k < 4; k++) {
					if (m1[i].binary[k] == m1[h].binary[k]) {
						count++;
					}
				}
				if (count == 3) {//1개만 다를때 머징
					if (Second > 0) {
						temp[0] = m1[i].merging[0];
						temp[1] = m1[i].merging[1];
						temp[2] = m1[h].merging[0];
						temp[3] = m1[h].merging[1];
						for (int t = 0; t < Second; t++) {
							for (int e = 0; e < 4; e++) {
								for (int m = 0; m < 4; m++) {
									if (m2[t].merging[e] == temp[m]) {
										same++;
									}
								}
							}
							if (same == 4) {
								cnt++;//cnt에 값이 있으면 중복되는 pi가 있다는것
							}
							same = 0;
						}
					}
					if (cnt == 0) {
						second1++;
						m2[mnumber].merging[0] = m1[i].merging[0];
						m2[mnumber].merging[1] = m1[i].merging[1];
						m2[mnumber].merging[2] = m1[h].merging[0];
						m2[mnumber].merging[3] = m1[h].merging[1];
						for (int p = 0; p < 4; p++) {
							if (m1[i].binary[p] == m1[h].binary[p]) {
								m2[mnumber].binary[p] = m1[i].binary[p];
							}
							else {
								m2[mnumber].binary[p] = 9;//나중에 -로 바꿔서 출력
							}
						}
						mnumber++;
						Second++;
					}
				}
				count = 0;
				cnt = 0;
			}
		}
	}
	if (first2 > 0) {
		for (int i = first0 + first1; i < first0 + first1 + first2; i++) {
			for (int h = first0 + first1 + first2; h < first0 + first1 + first2 + first3; h++) {
				for (int k = 0; k < 4; k++) {
					if (m1[i].binary[k] == m1[h].binary[k]) {
						count++;
					}
				}
				if (count == 3) {//1개만 다를때 머징
					if (Second > 0) {
						temp[0] = m1[i].merging[0];
						temp[1] = m1[i].merging[1];
						temp[2] = m1[h].merging[0];
						temp[3] = m1[h].merging[1];
						for (int t = 0; t < Second; t++) {
							for (int e = 0; e < 4; e++) {
								for (int m = 0; m < 4; m++) {
									if (m2[t].merging[e] == temp[m]) {
										same++;
									}
								}
							}
							if (same == 4) {
								cnt++;//cnt에 값이 있으면 중복되는 pi가 있다는것
							}
							same = 0;
						}
					}
					if (cnt == 0) {
						second2++;
						m2[mnumber].merging[0] = m1[i].merging[0];
						m2[mnumber].merging[1] = m1[i].merging[1];
						m2[mnumber].merging[2] = m1[h].merging[0];
						m2[mnumber].merging[3] = m1[h].merging[1];
						for (int p = 0; p < 4; p++) {
							if (m1[i].binary[p] == m1[h].binary[p]) {
								m2[mnumber].binary[p] = m1[i].binary[p];
							}
							else {
								m2[mnumber].binary[p] = 9;//나중에 -로 바꿔서 출력
							}
						}
						mnumber++;
						Second++;
					}
				}
				count = 0;
				cnt = 0;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////////////머징한거 출력
	key = getch();
	if (key == 32) {
		system("cls");
		printf("2차 Merging\n\n");
		for (int i = 0; i < mnumber; i++) {
			if (enter == second0 || enter == second0 + second1 || enter == second0 + second1 + second2) {
				printf("=======================================\n");
			}
			printf("(%d,%d,%d,%d)         ", m2[i].merging[0], m2[i].merging[1], m2[i].merging[2], m2[i].merging[3]);
			for (int j = 0; j < 4; j++) {
				if (m2[i].binary[j] == 9) {
					printf("-");
				}
				else {
					printf("%d", m2[i].binary[j]);
				}
			}
			printf("\n");
			enter++;
		}
	}
	Sec_result = second0 + second1 + second2;
}
void Third_Merging()//세번째 머징
{
	int count = 0;//머징 조건에 적합한지 찾을 변수
	int mnumber = 0;//m3순서
	int enter = 0;
	int same = 0;//중복체크 해줄 변수
	int temp[8] = { 0 };//중복확인하려는 p.i값 잠시 넣어두는 배열
	int cnt = 0;//똑같은 pi의 개수
	if (second0 > 0 && second1 > 0) {
		for (int i = 0; i < second0; i++) {
			for (int h = second0; h < second0 + second1; h++) {
				for (int k = 0; k < 4; k++) {
					if (m2[i].binary[k] == m2[h].binary[k]) {
						count++;
					}
				}
				if (count == 3) {//1개만 다를때 머징
					if (third0 > 0) {
						for (int y = 0; y < 4; y++) {
							temp[y] = m2[i].merging[y];
						}
						temp[4] = m2[h].merging[0];
						temp[5] = m2[h].merging[1];
						temp[6] = m2[h].merging[2];
						temp[7] = m2[h].merging[3];
						for (int t = 0; t < third0; t++) {
							for (int e = 0; e < 8; e++) {
								for (int m = 0; m < 8; m++) {
									if (m3[t].merging[e] == temp[m]) {
										same++;
									}
								}
							}
							if (same == 8) {
								cnt++;//cnt에 값이 있으면 중복되는 pi가 있다는것
							}
							same = 0;
						}
					}
					if (cnt == 0) {
						for (int y = 0; y < 4; y++) {
							m3[mnumber].merging[y] = m2[i].merging[y];
						}
						m3[mnumber].merging[4] = m2[h].merging[0];
						m3[mnumber].merging[5] = m2[h].merging[1];
						m3[mnumber].merging[6] = m2[h].merging[2];
						m3[mnumber].merging[7] = m2[h].merging[3];
						for (int p = 0; p < 4; p++) {
							if (m2[i].binary[p] == m2[h].binary[p]) {
								m3[mnumber].binary[p] = m2[i].binary[p];
							}
							else {
								m3[mnumber].binary[p] = 9;//나중에 -로 바꿔서 출력
							}
						}
						mnumber++;
						third0++;
					}
				}
				count = 0;
				cnt = 0;
			}
		}
	}
	if (second1 > 0 && second2 > 0) {
		for (int i = second0; i < second0 + second1; i++) {
			for (int h = second0 + second1; h < second0 + second1 + second2; h++) {
				for (int k = 0; k < 4; k++) {
					if (m2[i].binary[k] == m2[h].binary[k]) {
						count++;
					}
				}
				if (count == 3) {//1개만 다를때 머징
					if (third1 > 0) {
						for (int y = 0; y < 4; y++) {
							temp[y] = m2[i].merging[y];
						}
						temp[4] = m2[h].merging[0];
						temp[5] = m2[h].merging[1];
						temp[6] = m2[h].merging[2];
						temp[7] = m2[h].merging[3];
						for (int t = 0; t < third1; t++) {
							for (int e = 0; e < 8; e++) {
								for (int m = 0; m < 8; m++) {
									if (m3[t].merging[e] == temp[m]) {
										same++;
									}
								}
							}
							if (same == 8) {
								cnt++;//cnt에 값이 있으면 중복되는 pi가 있다는것
							}
							same = 0;
						}
					}
					if (cnt == 0) {
						for (int y = 0; y < 4; y++) {
							m3[mnumber].merging[y] = m2[i].merging[y];
						}
						m3[mnumber].merging[4] = m2[h].merging[0];
						m3[mnumber].merging[5] = m2[h].merging[1];
						m3[mnumber].merging[6] = m2[h].merging[2];
						m3[mnumber].merging[7] = m2[h].merging[3];
						for (int p = 0; p < 4; p++) {
							if (m2[i].binary[p] == m2[h].binary[p]) {
								m3[mnumber].binary[p] = m2[i].binary[p];
							}
							else {
								m3[mnumber].binary[p] = 9;//나중에 -로 바꿔서 출력
							}
						}
						mnumber++;
						third1++;
					}
				}
				count = 0;
				cnt = 0;
			}
		}
	}
	Third = third0 + third1;
	//////////////////////////////////////////////////////////////////////////////////머징한거 출력
	key = getch();
	if (key == 32) {
		system("cls");
		printf("3차 Merging\n\n");
		for (int i = 0; i < Third; i++) {
			if (enter == third0) {
				printf("=======================================\n");
			}
			printf(" (");
			for (int h = 0; h < 8; h++) {
				printf("%d ", m3[i].merging[h]);
			}
			printf(")         ");
			for (int j = 0; j < 4; j++) {
				if (m3[i].binary[j] == 9) {
					printf("-");
				}
				else {
					printf("%d", m3[i].binary[j]);
				}
			}
			printf("\n");
			enter++;
		}
	}
}
void Fourth_Merging()//네번째 머징
{
	for (int j = 0; j < 16; j++) {
		m4[0].merging[j] = j;
	}
	for (int i = 0; i < 4; i++) {
		m4[0].binary[i] = '-';
	}
	key = getch();
	if (key == 32) {
		system("cls");
		printf(" 4차 Merging\n\n");
		printf(" (");
		for (int i = 0; i < 16; i++) {
			printf("%d ", m4[0].merging[i]);
		}
		printf(")       ");
		for (int j = 0; j < 4; j++) {
			printf("%c", m4[0].binary[j]);
		}
		printf("\n");
	}
}
void Search_pi() {//p.i 찾기
	int count = 0;
	int same = 0;
	int i;
	if (num == 16) {
		pnumber = 1;
		for (int k = 0; k < 16; k++) {
			pi[0].merging[k] = m4[0].merging[k];
		}
		for (int k = 0; k < 4; k++) {
			pi[0].binary[k] = 9;
		}
		pi[0].merging_num = 16;
		key = getch();
		if (key == 32) {
			system("cls");
			printf(" Prime implicants 출력\n\n");
			printf("(");
			for (int k = 0; k < 16; k++) {
				printf(" %d", pi[0].merging[k]);
			}
			printf(")");
		}
	}
	else if (Sec_result == 0) {//두번째 머징이 일어나지 않음
		pnumber = Fir_result;
		for (int h = 0; h < pnumber; h++) {
			for (int k = 0; k < 2; k++) {
				pi[h].merging[k] = m1[h].merging[k];
			}
			pi[h].merging_num = 2;
			for (int k = 0; k < 4; k++) {
				pi[h].binary[k] = m1[h].binary[k];
			}
		}
	}
	else {
		if (Third > 0) {//세번째 머징이 일어났을경우
			i = 0;//m3배열 순서
			while (count < Sec_result) {
				for (int j = 0; j < 4; j++) {//m2배열 merging배열 순서
					for (int k = 0; k < 8; k++) {//m3 배열 merging배열 순서
						if (m3[i].merging[k] == m2[count].merging[j]) {
							same++;
						}
					}
				}
				if (same == 4) {//똑같은게 있음 더 볼 필요X
					same = 0;
					i = 0;
					count++;
				}
				else {
					if (i == Third - 1) {//똑같은게 없음 pi로 추가
						for (int j = 0; j < 4; j++) {
							pi[pnumber].merging[j] = m2[count].merging[j];//pi.merging배열에 추가로 넣어주기
							pi[pnumber].binary[j] = m2[count].binary[j];//pi.binary배열에 이진수 넣어주기
						}
						pi[pnumber].merging_num = 4;
						i = 0;
						pnumber++;
						count++;
					}
					else {
						i++;
					}
					same = 0;
				}
			}
			for (int h = 0; h < Third; h++) {//m3에 있는 pi들 pi배열에 넣어주기
				for (int k = 0; k < 8; k++) {
					pi[pnumber].merging[k] = m3[h].merging[k];
				}
				for (int k = 0; k < 4; k++) {
					pi[pnumber].binary[k] = m3[h].binary[k];
				}
				pi[pnumber].merging_num = 8;
				pnumber++;
			}
		}
		else if (Third == 0) {//세번재 머징이 일어나지 않음
			count = 0;
			pnumber = 0;
			same = 0;
			i = 0;//m2배열 순서
			while (count < Fir_result) {
				for (int j = 0; j < 2; j++) {//m1배열 merging배열 순서
					for (int k = 0; k < 4; k++) {//m2 배열 merging배열 순서
						if (m2[i].merging[k] == m1[count].merging[j]) {
							same++;
						}
					}
				}
				if (same == 2) {//똑같은게 있음 더 볼 필요X
					same = 0;
					i = 0;
					count++;
				}
				else {
					if (i == Sec_result - 1) {//똑같은게 없음 pi로 추가
						for (int j = 0; j < 2; j++) {
							pi[pnumber].merging[j] = m1[count].merging[j];
						}//pi.merging배열에 추가로 넣어주기
						pi[pnumber].merging_num = 2;
						for (int j = 0; j < 4; j++) {
							pi[pnumber].binary[j] = m1[count].binary[j];
						}//pi.binary배열에 이진수 넣어주기
						i = 0;
						pnumber++;
						count++;
					}
					else {
						i++;
					}
					same = 0;
				}
			}
			for (int h = 0; h < Sec_result; h++) {//m2에 있는 pi들 pi배열에 넣어주기
				for (int k = 0; k < 4; k++) {
					pi[pnumber].merging[k] = m2[h].merging[k];
					pi[pnumber].binary[k] = m2[h].binary[k];
				}
				pi[pnumber].merging_num = 4;
				pnumber++;
			}
		}
		key = getch();/////////////////pi결과 값 출력
		if (key == 32) {
			system("cls");
			printf(" Prime implicants 출력\n\n");
			for (int h = 0; h < pnumber; h++) {
				printf(" ( ");
				for (int j = 0; j < pi[h].merging_num; j++) {
					printf("%d ", pi[h].merging[j]);
				}
				printf(")\n");
			}
		}
	}
}
void Search_epi()
{
	int porder = 0;//pi순서
	int enumber = 0;//epi순서
	int arr[20][16] = { 0 };//c.x임시로 이차원배열에 넣어줄 배열
	int count = 0, del = 0;
	int essential = 0;
	int same = 0, eorder = 0, in = 0;
	char last[10][4] = { 0 };//마지막 수식(abcd a'b'c'd')넣어줄 배열
	if (pnumber != 1) {
		while (porder < pnumber) {
			for (int i = 0; i < pi[porder].merging_num; i++) {
				for (int j = 0; j < num; j++) {
					if (pi[porder].merging[i] == input[j].decimal) {
						c[porder].x[j] = 1;
					}
				}
			}
			porder++;
		}/////////////////////////도표안 x표시해주기
		key = getch();//////////////////////////////////////////////////////됴표 출력
		if (key == 32) {
			system("cls");
			printf("                       ");
			for (int i = 0; i < num; i++) {
				printf("%d  ", input[i].decimal);
			}
			printf("\n\n");//표 맨 위줄 출력(입력한 십진수들)
			for (int i = 0; i < pnumber; i++) {
				printf(" (");
				for (int j = 0; j < pi[i].merging_num; j++) {
					printf("%d ", pi[i].merging[j]);
				}
				if (pi[i].merging_num == 2) {
					printf(")               ");
				}
				else if (pi[i].merging_num == 4) {
					printf(")           ");
				}
				for (int h = 0; h < num; h++) {
					if (c[i].x[h] == 1) {
						printf(" 0 ");
					}
					else {
						printf("   ");
					}
				}
				printf("\n\n");
			}
			printf("%d", pnumber);
		}
		///////////////////////////////////////////////////epi 검색
		for (int i = 0; i < pnumber; i++) {
			for (int j = 0; j < num; j++) {
				arr[i][j] = c[i].x[j];
			}
		}
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < pnumber; j++) {
				if (arr[j][i] == 1) {//0 으로 표시되는 경우
					count++;
				}
			}
			if (count == 1) {//한 열에 0이 한개
				for (int h = 0; h < pnumber; h++) {
					if (arr[h][i] == 1) {//0이 한개인 열에서 0의 위치
						if (enumber > 0) {
							for (int s = 0; s < enumber; s++) {
								if (epi[s].pi_order == h) {
									in++;
								}
							}
						}
						else {
							in = 0;
						}
						if (in == 0) {
							for (int k = 0; k < pi[h].merging_num; k++) {//merging 넣어주기
								epi[enumber].merging[k] = pi[h].merging[k];
							}
							epi[enumber].merging_num = pi[h].merging_num;
							epi[enumber].pi_order = h;
							for (int k = 0; k < 4; k++) {// 이진수 넣어주기
								epi[enumber].binary[k] = pi[h].binary[k];
							}
							enumber++;
						}
						in = 0;
					}
				}
			}
			count = 0;
		}
		//////////////////////////////////////////////추가 epi 검색
		eorder = enumber;
		while (essential < pnumber) {
			for (int j = 0; j < pi[essential].merging_num; j++) {
				for (int h = 0; h < enumber; h++) {
					for (int k = 0; k < epi[h].merging_num; k++) {
						if (pi[essential].merging[j] == epi[h].merging[k]) {
							same++;
						}
					}
				}
			}
			if (same == 0) {
				for (int h = 0; h < pi[essential].merging_num; h++) {
					epi[eorder].merging[h] = pi[essential].merging[h];
				}
				epi[eorder].merging_num = pi[essential].merging_num;
				for (int k = 0; k < 4; k++) {
					epi[eorder].binary[k] = pi[essential].binary[k];
				}
				eorder++;
			}
			same = 0;
			essential++;
		}
		enumber = eorder;
		key = getch();
		if (key == 32) {
			system("cls");
			printf(" 최종 epi\n\n");
			for (int i = 0; i < enumber; i++) {
				printf("( ");
				for (int h = 0; h < epi[i].merging_num; h++) {
					printf("%d ", epi[i].merging[h]);
				}
				printf(")\n");
			}
		}
	}
	else if (pnumber == 1) {
		for (int h = 0; h < pi[0].merging_num; h++) {
			epi[0].merging[h] = pi[0].merging[h];
		}
		epi[0].merging_num = pi[0].merging_num;
		for (int k = 0; k < 4; k++) {
			epi[0].binary[k] = pi[0].binary[k];
		}
		enumber = 1;
	}
	key = getch();
	if (key == 32) {
		system("cls");
		printf(" < 0 0 0 0 = A B C D , 1 1 1 1 = a b c d >\n\n");
		for (int i = 0; i < enumber; i++) {
			printf("( ");
			for (int h = 0; h < epi[i].merging_num; h++) {
				printf("%d ", epi[i].merging[h]);
			}
			printf(") : ");
			for (int k = 0; k < 4; k++) {
				if (epi[i].binary[k] == 9) {
					printf(" - ");
				}
				else {
					printf(" %d ", epi[i].binary[k]);
				}
			}
			if (epi[i].binary[0] == 0) {
				last[i][0] = 'A';
			}
			else if (epi[i].binary[0] == 1) {
				last[i][0] = 'a';
			}
			if (epi[i].binary[1] == 0) {
				last[i][1] = 'B';
			}
			else if (epi[i].binary[1] == 1) {
				last[i][1] = 'b';
			}
			if (epi[i].binary[2] == 0) {
				last[i][2] = 'C';
			}
			else if (epi[i].binary[2] == 1) {
				last[i][2] = 'c';
			}
			if (epi[i].binary[3] == 0) {
				last[i][3] = 'D';
			}
			else if (epi[i].binary[3] == 1) {
				last[i][3] = 'd';
			}
			printf("  : ");
			for (int k = 0; k < 4; k++) {
				printf(" %c", last[i][k]);
			}
			printf("\n");
		}
		printf("\n");
		printf("   최종: ");
		for (int i = 0; i < enumber; i++) {
			for (int k = 0; k < 4; k++) {
				printf(" %c", last[i][k]);
			}
			if (i < enumber - 1)
				printf(" + ");
		}
		printf("\n");
	}
}
