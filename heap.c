#include<stdio.h>

int heap[16] = { 0 };//루트가 heap[1]부터 시작
int last = 0;

void up_heap(int n);
int down_heap();
void print();

void main() {
	int arr[15] = { 20,30,12,15,18,19,31,40,88,17,62,29,60,22,25};

	printf("---------힙 구성---------\n");
	for (int i = 0; i < 15; i++) up_heap(arr[i]);
	printf("---------힙 정렬---------\n");
	for (int i = 15; i >= 1; i--) {
		heap[i] = down_heap();
		print();
	}
}

void up_heap(int n) {
	int temp = 0, i = 0;

	last++;
	i = last;
	heap[i] = n;
	while (i != 1 && heap[i] > heap[i / 2]) {
		temp = heap[i];
		heap[i] = heap[i/2];
		heap[i / 2] = temp;
		i = i / 2;
	}
	print();
}

int down_heap() {
	int max = 0, temp = 0, largest = 0, i = 0;

	max = heap[1];
	heap[1] = heap[last];
	//heap[last] = 0;
	last--;
	i = 2;
	while (i <= last) {
		if (heap[i] < heap[i + 1]) largest = i + 1;
		else largest = i;
		if (heap[largest / 2] > heap[largest]) break;
		temp = heap[largest];
		heap[largest] = heap[largest / 2];
		heap[largest / 2] = temp;
		
		i = largest * 2;
	}
	return max;
}

void print() {
	for (int i = 0; i < 16; i++) {
		if (heap[i] == 0) printf("  ");
		else printf("%d ", heap[i]);
	}
	printf("\n");
}
