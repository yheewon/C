#include<stdio.h>

int stack[10] = { 0 };//10ĭ¥�� ����
int b1 = 0, b2 = 9, top1 = -1, top2 = 10;//bottom������, top������

void push(int s_num, int num);//int ���ù�ȣ int�Է��ϰ���� ��
void pop(int s_num);//int ���ù�ȣ
void print();//��� �Լ�

void main() {
	int s_num, num;
	print();
	while (1) {
		printf("���ù�ȣ �Է�(1/2) : ");
		scanf_s("%d", &s_num);
		printf("���� �Է� : ");
		scanf_s("%d", &num);
		push(s_num, num);
		printf("\n");
		print();
		printf("\n");
	}
}

void push(int s_num, int num) {
	if (top1 == b2) { //����1�� �迭 ��������
		printf("����1: ");
		pop(1);//�� �� �ε��� �� ����
	}
		
	else if (top2 == b1) { //����2�� �迭 ��������
		printf("����2: ");
		pop(2);//�� �� �ε��� �� ����
	}
		
	if (s_num == 1) {//1�� ����
		if (top1 + 1 == top2)//�迭�� ����
			pop(1);
		top1++;
		stack[top1] = num;
	}
	else if (s_num == 2) {//2������
		if (top1 + 1==top2)//�迭�� ����
			pop(2);
		top2--;
		stack[top2] = num;
	}
}

void pop(int s_num) {
	printf(" �����÷ο� �߻� \n");
	if (s_num == 1) {
		for (int i = b1; i < top1; i++)//bottom�����ͺ��� top�����ͱ��� 
			stack[i] = stack[i + 1];//�Ǿ� �� ����� ��°�� �Ű��ֱ� 
		top1--;//top������ �ϳ� �ٿ��ֱ�
	}

	else if (s_num == 2) {
		for (int i = b2; i > top2; i--)//bottom�����ͺ��� top�����ͱ��� 
			stack[i] = stack[i - 1];//�� �ް� ����� ��°�� �Ű��ֱ�
		top2++;//top������ �ϳ� �÷��ֱ�
	}
}

void print() {
	for (int i = 0; i < 10; i++) {
		printf("%d ", stack[i]);//�ƹ����� ������ 0���� ���
	}
	printf("\n");
}