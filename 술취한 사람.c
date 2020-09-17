#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
///////////////////// 0:술취한사람,★   1:빈공간,□  2:벽,■  3:집,▲  4:위치포인터,♡   10:전사분면   15:집이있는 사분면
int arr[12][12] = {
   { 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1 },
   { 1, 2, 2, 2, 2, 2, 1, 1, 2, 1, 1, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2 },
   { 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1 },
   { 1, 2, 2, 2, 2, 2, 1, 1, 2, 1, 2, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1 },
   { 1, 2, 2, 2, 2, 2, 1, 1, 2, 1, 2, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};//맵 
int p1, p2;//사람 위치
int h1, h2;// 집 위치
int step;//사람 걸음
int step2;//위치포인터 걸음
int pointer1, pointer2;//위치 포인터 위치
int key;
int i, j;
void PrintMap();
void People();//사람 위치 구하기
void House();//집 위치 구하기
void Move();//사람 랜덤으로 움직이기
void HouseZone();//집있는 사분면에서만 움직이게 하기
void Pointer();//위치포인터 위치 구하기
void PointerMoving();//위치포인터 움직이기
void Key();//키보드로 사람 움직이기
void HouseZone2();//집있는 사분면 키보드로만 움직이기
int main(void)
{
   srand(time(NULL));
   People();
   House();
   Pointer();
   PrintMap();
   while (arr[p1][p2] != 3) {
      Move();
      if (arr[p1][p2] != 3){
         PointerMoving();
         PrintMap();
      }
   }
   arr[p1][p2] = 0;
   arr[pointer1][pointer2] = 1;
   PrintMap();

}
void PrintMap()
{
   Sleep(100);
   system("cls");
   for (i = 0; i < 12; i++)
   {
      for (j = 0; j < 12; j++)
      {
         if (arr[i][j] == 0) {
            printf("★");
         }
         else if (arr[i][j] == 1 || arr[i][j] == 10 || arr[i][j] == 15) {
            printf("□");
         }
         else if (arr[i][j] == 2) {
            printf("■");
         }
         else if (arr[i][j] == 3) {
            printf("▲");
         }
         else if (arr[i][j] == 4) {
            printf("♡");
         }
      }
      printf("\n");
   }
}
void People()
{
   p1 = rand() % 12;
   p2 = rand() % 12;
   while (arr[p1][p2] == 2) {//배열 p1p2의 값이 벽의 값과 같을때 동안 계속 랜덤으로 돌려줌
      p1 = rand() % 12;
      p2 = rand() % 12;
   }
   arr[p1][p2] = 0;
}
void House()
{
   if (p1 > 5 && p2 > 5) {//사람은 4사분면에 위치
      h1 = rand() % 6;
      h2 = rand() % 6;
      while (arr[h1][h2] == 2) {
         h1 = rand() % 6;
         h2 = rand() % 6;
      }
      arr[h1][h2] = 3;//집은 2사분면에 위치
      for (i = 0; i < 6; i++) {
         for (j = 0; j < 6; j++) {
            if (arr[i][j] == 1) {
               arr[i][j] = 15;//2사분면 빈공간에 15넣기
            }
         }
      }
   }
   else if (p1 > 5 && p2 < 6) {//사람은 3사분면에 위치
      h1 = rand() % 6;
      h2 = rand() % 6 + 6;
      while (arr[h1][h2] == 2) {
         h1 = rand() % 6;
         h2 = rand() % 6 + 6;
      }
      arr[h1][h2] = 3;//집은 1사분면에 위치
      for (i = 0; i < 6; i++) {
         for (j = 6; j < 12; j++) {
            if (arr[i][j] == 1) {
               arr[i][j] = 15;//1사분면 빈공간에 15넣기
            }
         }
      }
   }
   else if (p1 < 6 && p2>5) {//사람은 1사분면에 위치
      h1 = rand() % 6 + 6;
      h2 = rand() % 6;
      while (arr[h1][h2] == 2) {
         h1 = rand() % 6 + 6;
         h2 = rand() % 6;
      }
      arr[h1][h2] = 3;//집은 3사분면에 위치
      for (i = 6; i < 12; i++) {
         for (j = 0; j < 6; j++) {
            if (arr[i][j] == 1) {
               arr[i][j] = 15;//3사분면 빈공간에 15넣기
            }
         }
      }
   }
   else if (p1 < 6 && p2 < 6) {//사람은 2사분면에 위치
      h1 = rand() % 6 + 6;
      h2 = rand() % 6 + 6;
      while (arr[h1][h2] == 2) {
         h1 = rand() % 6 + 6;
         h2 = rand() % 6 + 6;
      }
      arr[h1][h2] = 3;//집은 4사분면에 위치
      for (i = 6; i < 12; i++) {
         for (j = 6; j < 12; j++) {
            if (arr[i][j] == 1) {
               arr[i][j] = 15;//4사분면 빈공간에 15넣기
            }
         }
      }
   }
}
void Move()
{
   //0은 상     1은 좌     2는 우     3은 하
   step = rand() % 4;
   //scanf_s("%d", &step);
   if (step == 0) {
      if (p1 == 0) {//벽처리
         arr[p1][p2] = 0;
      }
      else if (arr[p1 - 1][p2] == 1) {//가려는 곳이 빈공간인 경우
         arr[p1][p2] = 1;
         p1 -= 1;
         arr[p1][p2] = 0;
         if (p1 + 1 == 6) {//3,4분면에서 1,2분면으로 이동
            if (p2 < 6) {//3사분면에서 2사분면으로 이동
               for (i = 6; i < 12; i++) {
                  for (j = 0; j < 6; j++) {
                     if (arr[i][j] == 1) {
                        arr[i][j] = 10;//3사분면 빈공간에 10넣기
                     }
                  }
               }
            }
            else {//4사분면에서 1사분면으로 이동
               for (i = 6; i < 12; i++) {
                  for (j = 6; j < 12; j++) {
                     if (arr[i][j] == 1) {
                        arr[i][j] = 10;//4사분면 빈공간에 10넣기
                     }
                  }
               }
            }
            arr[pointer1][pointer2] = 10;//3,4분면에 있는 위치 포인터에도 10 넣기
            Pointer();
         }//////////////전분면으로 이동못하게 하기
      }
      else if (arr[p1 - 1][p2] == 3) {//가려는 곳이 집인 경우
         arr[p1][p2] = 1;
         p1 -= 1;
         arr[p1][p2] = 3;
      }
      else if (arr[p1 - 1][p2] == 15) {//가려는 곳이 집이 있는 사분면인 경우
         arr[p1][p2] = 1;
         p1 -= 1;
         arr[p1][p2] = 0;
         arr[pointer1][pointer2] = 1;
         Pointer();
         PrintMap();
         HouseZone();
      }
      else if (arr[p1 - 1][p2] == 4) {//가려는 곳이 위치포인터가 있는곳일때
         arr[p1][p2] = 1;
         p1 -= 1;
         arr[p1][p2] = 0;
         //arr[pointer1][pointer2] = 1;
         PrintMap();
         Key();
      }
   }///////////////////////////////////////////////////step 0
   else if (step == 1) {
      if (p2 == 0) {//벽처리
         arr[p1][p2] = 0;
      }
      else if (arr[p1][p2 - 1] == 1) {//가려는 곳이 빈공간인 경우
         arr[p1][p2] = 1;
         p2 -= 1;
         arr[p1][p2] = 0;
         if (p2 + 1 == 6) {//1,4분면에서 2,3분면으로 이동하기
            if (p1 < 6) {//1사분면에서 2사분면으로 이동
               for (i = 0; i < 6; i++) {
                  for (j = 6; j < 12; j++) {
                     if (arr[i][j] == 1) {
                        arr[i][j] = 10;//1사분면 빈공간에 10넣기
                     }
                  }
               }
            }
            else {//4사분면에서 3사분면으로 이동
               for (i = 6; i < 12; i++) {
                  for (j = 6; j < 12; j++) {
                     if (arr[i][j] == 1) {
                        arr[i][j] = 10;//4사분면 빈공간에 10넣기
                     }
                  }
               }
            }
            arr[pointer1][pointer2] = 10;//1,4분면에 있는 위치 포인터에도 10 넣기
            Pointer();
         }////////////전분면 이동못하게 하기
      }
      else if (arr[p1][p2 - 1] == 3) {//가려는 곳이 집인 경우
         arr[p1][p2] = 1;
         p2 -= 1;
         arr[p1][p2] = 3;
      }
      else if (arr[p1][p2 - 1] == 15) {//가려는 곳이 집이 위치한 사분면일 경우
         arr[p1][p2] = 1;
         p2 -= 1;
         arr[p1][p2] = 0;
         arr[pointer1][pointer2] = 1;
         Pointer();
         PrintMap();
         HouseZone();
      }
      else if (arr[p1][p2 - 1] == 4) {//가려는 곳이 위치포인트가 위치하고 있는 경우
         arr[p1][p2] = 1;
         p2 -= 1;
         arr[p1][p2] = 0;
         //arr[pointer1][pointer2] = 1;
         PrintMap();
         Key();
      }
   }///////////////////////////////////////////////////step 1
   else if (step == 2) {
      if (p2 == 11) {//벽처리
         arr[p1][p2] = 0;
      }
      else if (arr[p1][p2 + 1] == 1) {//가려는 곳이 빈공간인 경우
         arr[p1][p2] = 1;
         p2 += 1;
         arr[p1][p2] = 0;
         if (p2 - 1 == 5) {//2,3분면에서 1,4분면으로 이동하기
            if (p1 < 6) {//2사분면에서 1사분면으로 이동
               for (i = 0; i < 6; i++) {
                  for (j = 0; j < 6; j++) {
                     if (arr[i][j] == 1) {
                        arr[i][j] = 10;//2사분면 빈공간에 10넣기
                     }
                  }
               }
            }
            else {//3사분면에서 4사분면으로 이동
               for (i = 6; i < 12; i++) {
                  for (j = 0; j < 6; j++) {
                     if (arr[i][j] == 1) {
                        arr[i][j] = 10;//3사분면 빈공간에 10넣기
                     }
                  }
               }
            }
            arr[pointer1][pointer2] = 10;//2,3분면에 있는 위치 포인터에도 10 넣기
            Pointer();
         }////////////////전분면으로 이동 못하게 하기
      }
      else if (arr[p1][p2 + 1] == 3) {//가려는 곳이 집인 경우
         arr[p1][p2] = 1;
         p2 += 1;
         arr[p1][p2] = 3;
      }
      else if (arr[p1][p2 + 1] == 15) {//가려는 곳이 집이 위치한 사분면일 경우
         arr[p1][p2] = 1;
         p2 += 1;
         arr[p1][p2] = 0;
         arr[pointer1][pointer2] = 1;
         Pointer();
         PrintMap();
         HouseZone();
      }
      else if (arr[p1][p2 + 1] == 4) {//가려는 곳이 위치포인터가 위치하고잇는 경우
         arr[p1][p2] = 1;
         p2 += 1;
         arr[p1][p2] = 0;
         //arr[pointer1][pointer2] = 1;
         PrintMap();
         Key();
      }
   }/////////////////////////////////////////////////////step2
   else if (step == 3) {
      if (p1 == 11) {//벽처리
         arr[p1][p2] = 0;
      }
      else if (arr[p1 + 1][p2] == 1) {//가려는 곳이 빈공간인 경우
         arr[p1][p2] = 1;
         p1 += 1;
         arr[p1][p2] = 0;
         if (p1 - 1 == 5) {//1,2분면에서 3,4분면으로 이동
            if (p2 < 6) {//2사분면에서 3사분면으로 이동
               for (i = 0; i < 6; i++)
               {
                  for (j = 0; j < 6; j++) {
                     if (arr[i][j] == 1) {
                        arr[i][j] = 10;//2사분면 빈공간에 10 넣기
                     }
                  }
               }
            }
            else {//1사분면에서 4사분면으로 이동
               for (i = 0; i < 6; i++) {
                  for (j = 6; j < 12; j++) {
                     if (arr[i][j] == 1) {
                        arr[i][j] = 10;//1사분면 빈공간에 10넣기
                     }
                  }
               }
            }
            arr[pointer1][pointer2] = 10;//1,2분면에 있는 위치 포인터에도 10 넣기
            Pointer();
         }
      }
      else if (arr[p1 + 1][p2] == 3) {//가려는 곳이 집인 경우
         arr[p1][p2] = 1;
         p1 += 1;
         arr[p1][p2] = 3;
      }
      else if (arr[p1 + 1][p2] == 15) {//가려는 곳이 집이 위치한 사분면일 경우
         arr[p1][p2] = 1;
         p1 += 1;
         arr[p1][p2] = 0;
         arr[pointer1][pointer2] = 1;
         Pointer();
         PrintMap();
         HouseZone();
      }
      else if (arr[p1 + 1][p2] == 4) {//가려는 곳이 위치포인터가 위치해 있는 경우
         arr[p1][p2] = 1;
         p1 += 1;
         arr[p1][p2] = 0;
         //arr[pointer1][pointer2] = 1;
         PrintMap();
         Key();
      }
   }////////////////////////////////////////////////////////step3
}
void HouseZone()
{
   int check = 0;
   while (arr[p1][p2] != 3)
   {
      step = rand() % 4;
      //scanf_s("%d", &step);
      if (step == 0) {
         if (p1 == 0) {//벽처리
            arr[p1][p2] = 0;
         }
         else if (arr[p1 - 1][p2] == 15) {//가려는 곳이 빈공간 일때
            arr[p1][p2] = 15;
            p1 -= 1;
            arr[p1][p2] = 0;
         }
         else if (arr[p1 - 1][p2] == 3) {//가려는 곳이 집일때
            arr[p1][p2] = 15;
            p1 -= 1;
            arr[p1][p2] = 3;
            check++;
         }
         else if (arr[p1 - 1][p2] == 4) {//가려는 곳에 위치포인터가 있을 때
            arr[p1][p2] = 15;
            p1 -= 1;
            //arr[pointer1][pointer2] = 15;
            arr[p1][p2] = 0;
            PrintMap();
            HouseZone2();
            check++;
         }
      }
      else if (step == 1) {
         if (p2 == 0) {//벽처리
            arr[p1][p2] = 0;
         }
         else if (arr[p1][p2 - 1] == 15) {//가려는 곳이 빈공간 일때
            arr[p1][p2] = 15;
            p2 -= 1;
            arr[p1][p2] = 0;
         }
         else if (arr[p1][p2 - 1] == 3) {//가려는 곳이 집 일때
            arr[p1][p2] = 15;
            p2 -= 1;
            arr[p1][p2] = 3;
            check++;
         }
         else if (arr[p1][p2 - 1] == 4) {//가려는 곳에 위치포인터가 있을 때
            arr[p1][p2] = 15;
            p2 -= 1;
            //arr[pointer1][pointer2] = 15;
            arr[p1][p2] = 0;
            PrintMap();
            HouseZone2();
            check++;
         }
      }
      else if (step == 2) {
         if (p2 == 11) {//벽처리
            arr[p1][p2] = 0;
         }
         else if (arr[p1][p2 + 1] == 15) {//가려는 공간이 빈공간 일때
            arr[p1][p2] = 15;
            p2 += 1;
            arr[p1][p2] = 0;
         }
         else if (arr[p1][p2 + 1] == 3) {//가려는 공간이 집 일때
            arr[p1][p2] = 15;
            p2 += 1;
            arr[p1][p2] = 3;
            check++;
         }
         else if (arr[p1][p2 + 1] == 4) {//가려는 공간에 위치포인터가 있을 때
            arr[p1][p2] = 15;
            p2 += 1;
            //arr[pointer1][pointer2] = 15;
            arr[p1][p2] = 0;
            PrintMap();
            HouseZone2();
            check++;
         }
      }
      else if (step == 3) {
         if (p1 == 11) {//벽처리
            arr[p1][p2] = 0;
         }
         else if (arr[p1 + 1][p2] == 15) {//가려는 곳이 빈공간 일때
            arr[p1][p2] = 15;
            p1 += 1;
            arr[p1][p2] = 0;
         }
         else if (arr[p1 + 1][p2] == 3) {//가려는 곳이 집 일때
            arr[p1][p2] = 15;
            p1 += 1;
            arr[p1][p2] = 3;
            check++;
         }
         else if (arr[p1 + 1][p2] == 4) {//가려는 곳에 위치 포인터가 있을 때
            arr[p1][p2] = 15;
            p1 += 1;
            //arr[pointer1][pointer2] = 15;
            arr[p1][p2] = 0;
            PrintMap();
            HouseZone2();
            check++;
         }
      }
      if (check == 0){
         PointerMoving();
         PrintMap();
      }
   }
}
void Pointer()
{
   if (p1 > 5 && p2 > 5) {//사람은 4분면에 위치
      pointer1 = rand() % 6 + 6;
      pointer2 = rand() % 6 + 6;
      while (arr[pointer1][pointer2] == 2 || arr[pointer1][pointer2] == 0 || arr[pointer1][pointer2] == 3) {
         pointer1 = rand() % 6 + 6;
         pointer2 = rand() % 6 + 6;
      }
      arr[pointer1][pointer2] = 4;
   }
   else if (p1 > 5 && p2 < 6) {//사람은 3사분면에 위치
      pointer1 = rand() % 6 + 6;
      pointer2 = rand() % 6;
      while (arr[pointer1][pointer2] == 2 || arr[pointer1][pointer2] == 0 || arr[pointer1][pointer2] == 3) {
         pointer1 = rand() % 6 + 6;
         pointer2 = rand() % 6;
      }
      arr[pointer1][pointer2] = 4;
   }
   else if (p1 < 6 && p2>5) {//사람은 1사분면에 위치
      pointer1 = rand() % 6;
      pointer2 = rand() % 6 + 6;
      while (arr[pointer1][pointer2] == 2 || arr[pointer1][pointer2] == 0 || arr[pointer1][pointer2] == 3) {
         pointer1 = rand() % 6;
         pointer2 = rand() % 6 + 6;
      }
      arr[pointer1][pointer2] = 4;
   }
   else if (p1 < 6 && p2 < 6) {//사람은 2사분면에 위치
      pointer1 = rand() % 6;
      pointer2 = rand() % 6;
      while (arr[pointer1][pointer2] == 2 || arr[pointer1][pointer2] == 0 || arr[pointer1][pointer2] == 3) {
         pointer1 = rand() % 6;
         pointer2 = rand() % 6;
      }
      arr[pointer1][pointer2] = 4;
   }
}
void PointerMoving()
{
   step2 = rand() % 4;
   //scanf_s("%d", &step2);
   printf("위치포인터 걸음:%d\n", step2);
   if (step2 == 0) {
      if (pointer1 == 0 || pointer1 == 6) {//벽처리 & 3,4분면에서 1,2분면 못넘어가게하기
         arr[pointer1][pointer2] = 4;
      }
      else if (arr[pointer1 - 1][pointer2] == 1) {//가려는 곳이 빈공간 일때
         arr[pointer1][pointer2] = 1;
         pointer1 -= 1;
         arr[pointer1][pointer2] = 4;
      }
      else if (arr[pointer1 - 1][pointer2] == 15) {
         arr[pointer1][pointer2] = 15;
         pointer1 -= 1;
         arr[pointer1][pointer2] = 4;
      }
      else if (arr[pointer1 - 1][pointer2] == 0) {//가려는 곳에 사람이 있을 때
         arr[pointer1][pointer2] = 1;
         pointer1 -= 1;
         arr[pointer1][pointer2] = 0;
         PrintMap();
         Key();
      }
   }
   else if (step2 == 1) {
      if (pointer2 == 0 || pointer2 == 6) {
         arr[pointer1][pointer2] = 4;
      }
      else if (arr[pointer1][pointer2 - 1] == 1) {//가려는 곳이 빈공간 일 때
         arr[pointer1][pointer2] = 1;
         pointer2 -= 1;
         arr[pointer1][pointer2] = 4;
      }
      else if (arr[pointer1][pointer2 - 1] == 15) {
         arr[pointer1][pointer2] = 15;
         pointer2 -= 1;
         arr[pointer1][pointer2] = 4;
      }

      else if (arr[pointer1][pointer2 - 1] == 0) {//가려는 곳에 사람이 있을 때
         arr[pointer1][pointer2] = 1;
         pointer2 -= 1;
         arr[pointer1][pointer2] = 0;
         PrintMap();
         Key();
      }
   }
   else if (step2 == 2) {
      if (pointer2 == 5 || pointer2 == 11) {//벽처리
         arr[pointer1][pointer2] = 4;
      }
      else if (arr[pointer1][pointer2 + 1] == 1) {//가려는 곳이 빈공간 일 때
         arr[pointer1][pointer2] = 1;
         pointer2 += 1;
         arr[pointer1][pointer2] = 4;
      }
      else if (arr[pointer1][pointer2 + 1] == 15) {
         arr[pointer1][pointer2] = 15;
         pointer2 += 1;
         arr[pointer1][pointer2] = 4;
      }
      else if (arr[pointer1][pointer2 + 1] == 4) {//가려는 곳에 사람이 있을 때
         arr[pointer1][pointer2] = 1;
         pointer2 += 1;
         arr[pointer1][pointer2] = 0;
         PrintMap();
         Key();
      }
   }
   else if (step2 == 3) {
      if (pointer1 == 11 || pointer1 == 5) {//벽처리
         arr[pointer1][pointer2] = 4;
      }
      else if (arr[pointer1 + 1][pointer2] == 1) {//가려고 하는곳이 빈공간 일 때
         arr[pointer1][pointer2] = 1;
         pointer1 += 1;
         arr[pointer1][pointer2] = 4;
      }
      else if (arr[pointer1 + 1][pointer2] == 15) {
         arr[pointer1][pointer2] = 15;
         pointer1 += 1;
         arr[pointer1][pointer2] = 4;
      }
      else if (arr[pointer1 + 1][pointer2] == 1) {//가려고 하는곳에 사람이 있을 때
         arr[pointer1][pointer2] = 1;
         pointer1 += 1;
         arr[pointer1][pointer2] = 0;
         PrintMap();
         Key();
      }
   }
}
void Key()
{
   //72:상      75:좌       77:우        80:하
   int stop = 0;//Key함수그만두게할 변수
   while (stop == 0) {
      key = getch();
      if (key == 224) {
         key = getch();
      }
      if (key == 72) {
         if (p1 == 0) {//벽처리
            arr[p1][p2] = 0;
         }
         else if (arr[p1 - 1][p2] == 1) {//가려는 곳이 빈공간 일 때
            arr[p1][p2] = 1;
            p1 -= 1;
            arr[p1][p2] = 0;
            if (p1 + 1 == 6) {//3,4분면에서 1,2분면 이동
               if (p2 < 6) {//3사분면에서 2사분면 이동
                  for (i = 6; i < 12; i++) {
                     for (j = 0; j < 6; j++) {
                        if (arr[i][j] == 1) {
                           arr[i][j] = 10;
                        }
                     }
                  }
               }
               else {//4사분면에서 1사분면 이동
                  for (i = 6; i < 12; i++) {
                     for (j = 6; j < 12; j++) {
                        if (arr[i][j] == 1) {
                           arr[i][j] = 10;
                        }
                     }
                  }
               }
               arr[pointer1][pointer2] = 10;
               stop += 1;
               Pointer();//////////////////////////////이건 써야하는건지 잘모르게따................
            }
         }
         else if (arr[p1 - 1][p2] == 3) {//가려는 곳이 집일 때
            arr[p1][p2] = 1;
            p1 -= 1;
            arr[p1][p2] = 3;
            stop -= 1;
         }
         else if (arr[p1 - 1][p2] == 15) {//가려는 곳이 집이 위치해있는 사분면일 경우
            arr[p1][p2] = 1;
            p1 -= 1;
            arr[p1][p2] = 0;
            if (p1 + 1 == 6) {//사분면 이동
               stop += 1;
               arr[pointer1][pointer2] = 1;
               Pointer();
               PrintMap();
               HouseZone();
            }
         }
      }
      else if (key == 75) {
         if (p2 == 0) {//벽처리
            arr[p1][p2] = 0;
         }
         else if (arr[p1][p2 - 1] == 1) {//가려고 하는곳이 빈공간일때
            arr[p1][p2] = 1;
            p2 -= 1;
            arr[p1][p2] = 0;
            if (p2 + 1 == 6) {//1,4분면에서 2,3분면으로 이동
               if (p1 < 6) {//1사분면에서 2사분면 이동
                  for (i = 0; i < 6; i++) {
                     for (j = 6; j < 12; j++) {
                        if (arr[i][j] == 1) {
                           arr[i][j] = 10;//1사분면 빈공간 10 넣기
                        }
                     }
                  }
               }
               else {//4분면에서 3사분면으로 이동
                  for (i = 6; i < 12; i++) {
                     for (j = 6; j < 12; j++) {
                        if (arr[i][j] == 1) {
                           arr[i][j] = 10;//4사분면 빈공간 10 넣기
                        }
                     }

                  }
               }
               arr[pointer1][pointer2] = 10;
               stop += 1;
               Pointer();
            }
         }
         else if (arr[p1][p2 - 1] == 3) {//가려는 곳이 집일 
            arr[p1][p2] = 1;
            p2 -= 1;
            arr[p1][p2] = 3;
            stop += 1;
         }
         else if (arr[p1][p2 - 1] == 15) {//가려는 곳이 집이 위치해있는 사분면일 경우
            arr[p1][p2] = 1;
            p2 -= 1;
            arr[p1][p2] = 0;
            if (p2 + 1 == 6) {//사분면 이동
               stop += 1;
               arr[pointer1][pointer2] = 1;
               Pointer();
               PrintMap();
               HouseZone();
            }
         }
      }
      else if (key == 77) {
         if (p2 == 11) {//벽처리
            arr[p1][p2] = 0;
         }
         else if (arr[p1][p2 + 1] == 1) {//가려는 곳이 빈공간 일 경우
            arr[p1][p2] = 1;
            p2 += 1;
            arr[p1][p2] = 0;
            if (p2 - 1 == 5) {//2,3분면에서 1,4분면으로 이동
               if (p1 < 6) {//2분면에서 1분면으로 이동
                  for (i = 0; i < 6; i++) {
                     for (j = 0; j < 6; j++) {
                        if (arr[i][j] == 1) {
                           arr[i][j] = 10;//2사분면 빈공간 10 넣기
                        }
                     }
                  }
               }
               else {//3분면에서 4분면으로 이동
                  for (i = 6; i < 12; i++) {
                     for (j = 0; j < 6; j++) {
                        if (arr[i][j] == 1) {
                           arr[i][j] = 10;//3사분면 빈공간 10 넣기
                        }
                     }
                  }
               }
               arr[pointer1][pointer2] = 10;
               stop += 1;
               Pointer();
            }
         }
         else if (arr[p1][p2 + 1] == 3) {//가려는 곳이 집인 경우
            arr[p1][p2] = 1;
            p2 += 1;
            arr[p1][p2] = 3;
            stop += 1;
         }
         else if (arr[p1][p2 + 1] == 15) {//가려는 곳이  집이 잇는 사분면인 경우
            arr[p1][p2] = 1;
            p2 += 1;
            arr[p1][p2] = 0;
            if (p2 - 1 == 5) {
               stop += 1;
               arr[pointer1][pointer2] = 1;
               Pointer();
               PrintMap();
               HouseZone();
            }
         }
      }
      else if (key == 80) {
         if (p1 == 11) {//벽처리
            arr[p1][p2] = 0;
         }
         else if (arr[p1 + 1][p2] == 1) {//가려는곳이 빈공간인 경우
            arr[p1][p2] = 1;
            p1 += 1;
            arr[p1][p2] = 0;
            if (p1 - 1 == 5) {//1,2분면에서 3,4분면으로 이동
               if (p2 < 6) {//2분면에서 3분면으로 이동
                  for (i = 0; i < 6; i++) {
                     for (j = 0; j < 6; j++) {
                        if (arr[i][j] == 1) {
                           arr[i][j] = 10;//2분면 빈공간 10으로 만들기
                        }
                     }
                  }
               }
               else {//1분면에서 4분면으로 이동
                  for (i = 0; i < 6; i++) {
                     for (j = 6; j < 12; j++) {
                        if (arr[i][j] == 1)
                        {
                           arr[i][j] = 10;//1분면 빈공간 10으로 만들기
                        }
                     }
                  }
               }
            }
         }
         else if (arr[p1 + 1][p2] == 3) {
            arr[p1][p2] = 1;
            p1 += 1;
            arr[p1][p2] = 3;
            stop += 1;
         }
         else if (arr[p1 + 1][p2] == 15) {
            arr[p1][p2] = 1;
            p1 += 1;
            arr[p1][p2] = 0;
            if (p1 - 1 == 5) {
               stop += 1;
               arr[pointer1][pointer2] = 1;
               Pointer();
               PrintMap();
               HouseZone();
            }
         }
      }
      PrintMap();
   }
}
void HouseZone2()
{
   while (arr[p1][p2] != 3) {
      key = getch();
      if (key == 224) {
         key = getch();
      }
      if (key == 72) {
         if (p1 == 0) {//벽처리
            arr[p1][p2] = 0;
         }
         else if (arr[p1 - 1][p2] == 15) {//가려는 곳이 빈공간 일때
            arr[p1][p2] = 15;
            p1 -= 1;
            arr[p1][p2] = 0;
         }
         else if (arr[p1 - 1][p2] == 3) {//가려는 곳이 집일때
            arr[p1][p2] = 15;
            p1 -= 1;
            arr[p1][p2] = 3;
         }
      }
      else if (key == 75) {
         if (p2 == 0) {//벽처리
            arr[p1][p2] = 0;
         }
         else if (arr[p1][p2 - 1] == 15) {//가려는 곳이 빈공간 일때
            arr[p1][p2] = 15;
            p2 -= 1;
            arr[p1][p2] = 0;
         }
         else if (arr[p1][p2 - 1] == 3) {//가려는 곳이 집 일때
            arr[p1][p2] = 15;
            p2 -= 1;
            arr[p1][p2] = 3;
         }
      }
      else if (key == 77) {
         if (p2 == 11) {//벽처리
            arr[p1][p2] = 0;
         }
         else if (arr[p1][p2 + 1] == 15) {//가려는 공간이 빈공간 일때
            arr[p1][p2] = 15;
            p2 += 1;
            arr[p1][p2] = 0;
         }
         else if (arr[p1][p2 + 1] == 3) {//가려는 공간이 집 일때
            arr[p1][p2] = 15;
            p2 += 1;
            arr[p1][p2] = 3;
         }
      }
      else if (key == 80) {
         if (p1 == 11) {//벽처리
            arr[p1][p2] = 0;
         }
         else if (arr[p1 + 1][p2] == 15) {//가려는 곳이 빈공간 일때
            arr[p1][p2] = 15;
            p1 += 1;
            arr[p1][p2] = 0;
         }
         else if (arr[p1 + 1][p2] == 3) {//가려는 곳이 집 일때
            arr[p1][p2] = 15;
            p1 += 1;
            arr[p1][p2] = 3;
         }
      }
      PrintMap();
   }
}
