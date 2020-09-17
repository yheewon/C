#define _CRT_SECURE_NO_WARNINGS    // strcpy 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>
#include <string.h>
#include<Windows.h>
typedef struct Person {
	char name[20];
	char number[20];
	struct person*next;
}person;
struct Person *temp;
void Addnode(person*head);//노드 추가 함수
void Print(person*head);//출력함수
int main()
{
	person*head = malloc(sizeof(person));
	head->next = NULL;
	while (1) {
		Addnode(head);
		system("cls");
		Print(head);
	}
}
void Addnode(person*head)
{
	person*newnode = malloc(sizeof(person));
	int check;//이름 비교해줄 변수
	int check2;//학번 비교해줄 변수
	person *per = head->next;
	person *p = head;
	printf("-------------\n");
	printf("이름입력:");
	scanf("%s", &newnode->name);
	printf("\n");
	printf("학번입력:");
	scanf("%s", &newnode->number);
	printf("-------------\n\n");
	if (per == NULL)
	{
		head->next = newnode;
		newnode->next = NULL;
	}
	else
	{
		while (per != NULL)
		{
			check = strcmp(per->name, newnode->name);
			if (check > 0) {
				newnode->next = per;
				p->next = newnode;
				break;
			}
			else if (check == 0)
			{
				check2 = strcmp(per->number, newnode->number);
				if (check2 > 0)
				{
					newnode->next = per;
					p->next = newnode;
					break;
				}
				else if (check2<0)
				{
					if (per->next == NULL) {
						per->next = newnode;
						newnode->next = NULL;
						break;
					}
					else
					{
						p = p->next;
						per = per->next;
					}
				}
				else {
					p = p->next;
					per = per->next;
				}
			}
			else if (check<0)
			{
				if (per->next == NULL)
				{
					per->next = newnode;
					newnode->next = NULL;
					break;
				}
				else
				{
					p = p->next;
					per = per->next;
				}
			}
			else
			{
				p = p->next;
				per = per->next;
			}
		}
	}
}
void Print(person*head)
{
	person*node;
	node = head->next;
	puts("출력");
	while (node != NULL)
	{
		printf("------------------------------\n");
		printf("이름: %s   학번: %s\n", node->name, node->number);
		printf("------------------------------\n");
		node = node->next;
	}
}
