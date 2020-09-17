#include<stdio.h>

int stack[10] = { 0 };//10칸짜리 스택
int b1 = 0, b2 = 9, top1 = -1, top2 = 10;//bottom포인터, top포인터

void push(int s_num, int num);//int 스택번호 int입력하고싶은 수
void pop(int s_num);//int 스택번호
void print();//출력 함수

void main() {
	int s_num, num;
	print();
	while (1) {
		printf("스택번호 입력(1/2) : ");
		scanf_s("%d", &s_num);
		printf("숫자 입력 : ");
		scanf_s("%d", &num);
		push(s_num, num);
		printf("\n");
		print();
		printf("\n");
	}
}

void push(int s_num, int num) {
	if (top1 == b2) { //스택1이 배열 다차지함
		printf("스택1: ");
		pop(1);//맨 앞 인덱스 값 삭제
	}
		
	else if (top2 == b1) { //스택2가 배열 다차지함
		printf("스택2: ");
		pop(2);//맨 끝 인덱스 값 삭제
	}
		
	if (s_num == 1) {//1번 스택
		if (top1 + 1 == top2)//배열이 꽉참
			pop(1);
		top1++;
		stack[top1] = num;
	}
	else if (s_num == 2) {//2번스택
		if (top1 + 1==top2)//배열이 꽉참
			pop(2);
		top2--;
		stack[top2] = num;
	}
}

void pop(int s_num) {
	printf(" 오버플로우 발생 \n");
	if (s_num == 1) {
		for (int i = b1; i < top1; i++)//bottom포인터부터 top포인터까지 
			stack[i] = stack[i + 1];//맨앞 값 지우고 통째로 옮겨주기 
		top1--;//top포인터 하나 줄여주기
	}

	else if (s_num == 2) {
		for (int i = b2; i > top2; i--)//bottom포인터부터 top포인터까지 
			stack[i] = stack[i - 1];//맨 뒷값 지우고 통째로 옮겨주기
		top2++;//top포인터 하나 늘려주기
	}
}

void print() {
	for (int i = 0; i < 10; i++) {
		printf("%d ", stack[i]);//아무값도 없으면 0으로 출력
	}
	printf("\n");
}