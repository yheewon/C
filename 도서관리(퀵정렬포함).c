 #include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct book {
	char title[20];
	char auther[20];
	int price;
	char code[20];
	struct book* next;
}book;

book *temp;
int count = 0;

void swap(book *arr[], int left, int right)//스왑
{
	temp = arr[left];
	arr[left] = arr[right];
	arr[right] = temp;
}
int partition(book *arr[], int left, int right) //파티션
{
	int pivot;
	int low, high;

	low = left;
	high = right + 1;
	pivot = arr[left]->price;
	do
	{
		do
			low++;
		while (low <= right && arr[low]->price < pivot);
		do
			high--;
		while (high >= left && arr[high]->price > pivot);
		if (low < high)
			swap(arr, low, high);
	} while (low < high);

	swap(arr, left, high);

	return high;
}
void quick_sort(book* arr[], int left, int right) // 퀵소트
{
	if (left < right)
	{
		int q = partition(arr, left, right);
		quick_sort(arr, left, q - 1);
		quick_sort(arr, q + 1, right);
	}

}
book *link(book *arr[], book*head, int coutn) //링크정렬
{
	head = head->next;
	for (int i = 1; i < count ; i++)
	{
		head = arr[i];
		head->next = (book*)malloc(sizeof(book));
		head->next = NULL;
		head->next = arr[i + 1];
		head = head->next;
	}
	head->next = arr[count];
	head = head->next;
	head->next = NULL;
	return head;

}


//뒤로 추가할때
book* AddNode(book* head)
{
	book* newnode = malloc(sizeof(book));

	while (head->next != NULL)
	{
		head = head->next;
	}
	while (getchar() != '\n');
	printf("제목:");
	gets(newnode->title);
	printf("저자:");
	gets(newnode->auther);
	printf("코드:");
	gets(newnode->code);
	printf("가격:");
	scanf_s("%d", &newnode->price);

	head -> next = newnode;
	newnode -> next = NULL;
}
//출력
int PrintNode(book* head,int count2)
{
	book* start;
	int i = 1;
	start = head->next;
		while (start!= NULL)
		{
			printf("%d.제목:%s  저자:%s  코드:%s  가격:%d", i, start->title, start->auther, start->code, start->price);
			printf("\n\n");
			start = start->next;
			i++;
		}

}
//삭제
book* DeletNode(book *head)
{
	char title[20];
	book* start;
	book* pre;
	start = head;
	start->next = head->next;
	pre = start;


	while (getchar() != '\n');
	printf("삭제할 제목명:");
	gets(title);
	while (strcmp(start->title, title) != 0 && start->next != NULL)
	{
		pre = start;
		start = start->next;
	}
	if (start->next == NULL)
	{
		printf("오류입니다\n");
		count++;
		return 0;
	}
	pre->next = start->next;
	free(start);

}
//메뉴
void menu()
{
	printf("****************************\t\t\n");
	printf("*1.책정보 입력             *\t\t\n");
	printf("*2.책정보 출력             *\t\t\n");
	printf("*3.책정보 검색(도서명)     *\t\t\n");
	printf("*4.책정보 검색(코드명)     *\t\t\n");
	printf("*5.책정보 수정             *\t\t\n");
	printf("*6.책정보 삭제             *\t\t\n");
	printf("*7.책정보 정렬(가격순)     *\t\t\n");
	printf("*0.종료                    *\t\t\n");
	printf("****************************\t\t\n");
}
//책이름으로 찾기
book* SerchNode_Title(book* head)
{
	book*start;
	char title[20];
	start = head->next;
	while (getchar() != '\n');
	printf("도서명을 입력하세요\n");
	gets(title);
	while (strcmp(start->title, title) != 0 && start->next != NULL)
	{
		start = start->next;
	}
	printf("제목:%s  저자:%s  코드:%s  가격:%d\n", start->title, start->auther, start->code, start->price);

}
//코드명으로 찾기
book*SerchNode_Code(book*head)
{
	book*start; 
	char code[20];
	start = head->next;
	while (getchar() != '\n');
	printf("코드를 입력하세요\n");
	gets(code);
	while (strcmp(start->code, code) != 0 && start->next != NULL)
	{
		start = start->next;
	}
	printf("제목:%s  저자:%s  코드:%s  가격:%d\n", start->title, start->auther, start->code, start->price);

}
//책이름으로 찾고 수정
book*ChangeNode(book*head)
{
	book*start;
	char title[20];
	start = head->next;
	while (getchar() != '\n');
	printf("도서명을 입력하세요\n");
	gets(title);
	while (strcmp(start->title, title) != 0 && start->next != NULL)
	{
		start = start->next;
	}
	while (getchar() != '\n');

	printf("제목:");
	gets(start->title);
	printf("저자:");
	gets(start->auther);
	printf("코드:");
	gets(start->code);
	printf("가격:");
	scanf_s("%d", &start->price);


}
int main()
{
	int choice;
	int count2 = 0;
	book*head = malloc(sizeof(book));
	book*arr[100];
	head ->next= NULL;
	for (;;)
	{
		menu();
		printf("번호를 입력하세요\n");
		scanf_s("%d", &choice);
		if (choice == 1)
		{
			AddNode(head);
			count++;
			system("cls");
		}
		else if (choice == 2)
		{
			PrintNode(head,count2);
			
		}
		else if (choice == 3)
		{
			SerchNode_Title(head);
			
		}
		else if (choice == 4)
		{
			SerchNode_Code(head);
			
		}
		else if (choice == 5)
		{
			ChangeNode(head);
		
		}
		else if (choice == 6)
		{
			DeletNode(head);
			count--;
		}
		else if (choice == 7)
		{
			temp = head;
			while (temp->next != NULL)
			{
				arr[0] = head;
				for (int i = 1; i < count + 1; i++)
				{
					arr[i] = temp->next;;
					temp = temp->next;
				}
			}
			quick_sort(arr, 1, count);
			head->next = arr[1];
			head = link(arr, head, count);
			head = arr[0];
		}
		else if (choice == 0)
		{
			printf("시스템 종료합니다\n");
			break;
		}
		else
		{
			printf("다시 입력하세요.\n");
		}
	}


}

