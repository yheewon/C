#include<stdio.h>

void printArr(int arr[]);//배열 출력함수
void shellSort(int arr[], int n);// 쉘정렬 함수
void insertSort(int arr[], int first, int last, int gap);//삽입정렬 함수

void main() {
	int arr[11] = { 10,8,6,20,4,3,22,1,0,15,16 };//정렬할 숫자 배열
        printf(“1701185 윤희원\n 정렬전 : ”);
	printArr(arr);
	shellSort(arr, 11);//크기가 11인 배열 arr로 쉘정렬 시작 
}

void printArr(int arr[]) {
	for (int i = 0; i < 11; i++) {
		printf(" %d", arr[i]);
	}
	printf("\n");
}

void shellSort(int arr[],int n){//(배열,배열사이즈)
	for (int gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;//만약 gap이 짝수이면 정렬을 더 효율적으로 하기 위해서 홀수로 만들어주기
		for (int i = 0; i < gap; i++) insertSort(arr, i, n - 1, gap);
		printf("gap : %d\n", gap);
		printArr(arr);//gap별로 정렬한 후 결과 출력
	}
}

void insertSort(int arr[], int first, int last, int gap) {//(배열, 시작위치, 마지막위치, gap)
	int temp;//두배열의 위치를 바꾸기 위해 잠시 값을 저장하기 위한 변수
	for (int i = first + gap; i <= last; i = i + gap) {
		temp = arr[i];
		for (int j = i - gap; j >= first&& temp < arr[j]; j = j - gap) {//temp < arr[j] 조건으로 두 배열의 위치를 바꿔줌
			arr[j + gap] = arr[j];
			arr[j] = temp;
		}
	}
}
