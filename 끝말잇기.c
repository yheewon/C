#include<stdio.h>
#include<string.h>
#include<Windows.h>
char arr3[10][20];
int idx = 0;
void Print();
void Remove();//arr3 10행이 넘어가면 맨위에서 부터 사라지게 하기
int main(void)
{
	char arr1[20] = "dog";
	char arr2[20];
	int last;//마지막 글자 들어있을 배열 위치
	printf("---------------------------------\n");
	strcpy_s(arr3[0], sizeof(arr2), arr1);//arr3배열 0행에 dog넣기
	printf("%s\n", arr3[0]);//dog출력
	while (1)
	{
		Remove();
		last = strlen(arr1) - 1;//
		gets(arr2);
		idx++;
		if (arr1[last] != arr2[0])
		{
			printf("게임종료\n");
			break;
		}
		if (idx >= 11)
		{
			idx -= 1;
		}
		strcpy_s(arr3[idx], sizeof(arr3[idx]), arr2);
		Remove();
		last = strlen(arr2) - 1;
		gets(arr1);
		idx++;
		if (arr2[last] != arr1[0])
		{
			printf("게임종료\n");
			break;
		}
		if (idx >= 11)
		{
			idx -= 1;
		}
		strcpy_s(arr3[idx], sizeof(arr3[idx]), arr1);
	}

}
void Print()
{
	printf("---------------------------------\n");
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			printf("%c", arr3[i][j]);
		}
		printf("\n");
	}
}
void Remove()
{
	if (idx >= 10)//arr3 10행이 넘어가면 맨위에서 부터 사라지게 하기
	{
		for (int i = 0; i < 10; i++)
		{
			strcpy_s(arr3[i], sizeof(arr3[i]), arr3[i + 1]);//i=0: arr3[1]의 문자열을 arr3[0]에 복사
		}
		system("cls");
		Print();
	}
}
