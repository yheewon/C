#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <process.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#pragma comment (lib, "ws2_32.lib")
#pragma warning(disable:4996)

using namespace std;

#define PORT   5500
#define BUFFERSIZE 100
#define NAMESIZE 30

unsigned  sendThread;
class THD {
protected:        // 자식 클래스에 상속 가능
   int map[10][6];
public:
   void Map();//맵 만들기
};

void THD::Map() {
   for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 6; j++) {
         if (i <= 2) map[i][j] = 1;//벽돌 세줄
         else map[i][j] = 0;//빈공간
      }
   }
}
class Ball : public THD {  // 공 조정 자식 클래스 (부모 클래스 상속)
private:
   int ballx, bally;//공 좌표
   int brick;//벽돌 갯수
   int time;//로컬 ㅌ타임


public:
   int Soc_Cli();
   static unsigned __stdcall sendMessage(void* arg);
   Ball();//생성자
   ~Ball();//소멸자

   void PrintMap();//출력

   void Play();//게임 실행 여부
   void Move();//게임 시작

   void Move_up();//공 올리는 함수
   void UP();//수직으로 상승
   void Right_up();//오른쪽으로 상승
   void Left_up();//왼쪽으로 상승
   void Move_down();//공 내리는 함수
   void Down();//수직으로 하강
   void Right_down();//오른쪽으로 하강
   void Left_down();//왼쪽으로 하강

   int mySocket;



};
int Ball::Soc_Cli()
{
   WSADATA wsadata;
   WSAStartup(MAKEWORD(2, 2), &wsadata);

   /*서버에 접속해서 걸린 시간을 보내주는 클라이언트 소켓생성*/
   mySocket = socket(PF_INET, SOCK_STREAM, 0);
   /*클라이언트 소켓생성에 실패하면 에러메시지를 출력하고 함수 종료*/
   if (mySocket == -1) {
      cout << "클라이언트 소켓을 생성하는데 실패 했습니다" << endl;
      return 0;
   }
   /*서버의 주소 정보를 저장할 구조체 serverAddress 선언*/
   sockaddr_in serverAddress;
   /*구조체를 0으로 초기화함*/
   memset(&serverAddress, 0, sizeof(serverAddress));
   /*서버의 IP 대입*/
   serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
   /*주소의 종류 대입*/
   serverAddress.sin_family = AF_INET;
   /*서버의 포트번호 대입*/
   serverAddress.sin_port = htons(PORT);
   /*서버에 접속*/
   if (connect(mySocket, (sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
      cout << "서버와 연결하는데 실패했습니다" << endl;
      return 0;
   }
   else
   {
      char greetMessage[BUFFERSIZE];  //서버에서 전송할 환영 메시지를 저장할 배열
                              /*서버에서 전송한 환영 메시지를 읽어 들임*/
      recv(mySocket, greetMessage, sizeof(greetMessage), 0);
      cout << greetMessage << endl;
      /*키보드 입력을 읽어 들여서 서버로 전송하는 sendMessage 함수를 멀티 쓰레드로 시작함*/
      unsigned long hSendThread = _beginthreadex(NULL, 0, sendMessage, (void*)mySocket, 0, &sendThread);
      /*서버에서 전송한 다른 클라이언트들의 메시지를 읽어 들여서 화면에 출력하는 receiveMessage 함수를 멀티 쓰레드로 시작함*/

      /*sendMessage 함수를 멀티 쓰레드로 실행하는 sendThread 가 종료 할때 까지 main 함수가 대기 하도록 함*/
      WaitForSingleObject((HANDLE)hSendThread, INFINITE);
      /*receiveMessage 함수를 멀티 쓰레드로 실행하는 receiveThread 가 종료 할때 까지 main 함수가 대기 하도록 함*/
      Play();
   }
   return 0;
}
unsigned __stdcall Ball::sendMessage(void* arg)
{
   /*서버와 데이터를 주고 받는 클라이언트 소켓을  멀티 쓰레드 시작시 main 함수에서 인자로 전달 받습니다. 인자로 전달 받은 클라이언트 소켓을 mySocket 에 대입합니다. */
   int mySocket1 = (int)arg;
   char myName[NAMESIZE]; //클라이언트 대화명을 저장할 배열
                     /*대화명과 키보드 입력내용을 하나로 묶어서 서버로 보낼 메시지를 저장할 배열*/
   cout << "클라이언트의 닉네임을 입력하세요 -->";
   fgets(myName, NAMESIZE, stdin); //입력 받은 대화명을 myName 에 대입
   myName[strlen(myName) - 1] = '\0'; //대화명 맨 끝에 NULL 문자를 추가
   char toServer[NAMESIZE + BUFFERSIZE];
   sprintf_s(toServer, NAMESIZE + BUFFERSIZE, "[%s] 님이  입장 하셨습니다", myName);
   printf("[%s]", toServer);
   /*“대화명 님이 입장하셨습니다” 라는 toServer 배열에 저장된 메시지를 서버로 전송*/
   send(mySocket1, toServer, sizeof(toServer), 0);
   system("cls");

   return 0;
}

Ball::Ball() {
   ballx = 9;//초기 공 x좌표
   bally = 1;//초기 공 y좌표
   brick = 18;//벽돌 갯수
   time = 0;
}
Ball::~Ball() {
   cout << "게임 종료" << endl;
}
void Ball::Play() {
   int play;//게임실행 여부

   int i = 0;


   while (i == 0) {
      system("cls");
      cout << "1. 게임 시작 " << endl;
      cout << "2. 게임 종료" << endl;
      cout << "번호를 입력하세요 :";
      cin >> play;
      if (play == 1) {
         ballx = 9;//초기 공 x좌표
         bally = 1;//초기 공 y좌표
         brick = 18;//벽돌 갯수
         time = 0;
         Move();//게임 시작
      }
      else if (play == 2) {
         i = 1;//게임 종료 for문 탈출
      }
   }

}
void Ball::Move() {
   system("cls");
   Map();
   PrintMap();
   int stop = 0;
   int key = _getch();
   if (key == 32) {//스페이스바 누르면 공 움직이기 시작
      while (stop == 0) {
         if (brick != 0) Move_up();
         else stop = 1;
      }
      cout << "벽돌을 다 깼습니다.";
      cout << "로컬타임 - 공 상승후에 하강하면서 바닥을 찍은 횟수:" << time << endl;
      Sleep(1000);
   }
}
void Ball::PrintMap() {
   for (int a = 0; a < 10; a++) {
      for (int b = 0; b < 6; b++) {
         if (a == ballx && b == bally) cout << "●";//공
         else if (map[a][b] == 1) cout << "■";//벽돌
         else if (map[a][b] == 0)cout << "  ";//빈칸
      }
      cout << endl;
   }
}
void Ball::Move_up() {
   int u;
   u = rand() % 3;
   if (u == 0) UP();
   if (u == 1) Right_up();
   if (u == 2)Left_up();
}
void Ball::Move_down() {
   int d;
   d = rand() % 3;
   if (d == 0) Down();
   if (d == 1) Right_down();
   if (d == 2) Left_down();
}
void Ball::UP() {
   while (map[ballx - 1][bally] != 1 && ballx >= 1) {//가려는 곳이 벽돌이 아니고 높이가 1보다 클동안 반복
      system("cls");
      ballx--;
      PrintMap();
      Sleep(10);
   }
   if (ballx >= 1) map[ballx - 1][bally] = 0, brick--;
   Move_down();

}
void Ball::Right_up() {
   int x;//임시로 높이 저장
   int stop = 0;//while문 멈출 변수
   x = ballx;
   while (x >= 1 && stop == 0) {
      system("cls");
      if (bally == 5)x = 0;//오른쪽 벽 끝에 있으면 while문 탈출
      if (map[ballx - 1][bally] == 1) {//공이 위치해 있는 곳 위에 벽돌 존재
         map[ballx - 1][bally] = 0;
         brick--;
         stop = 1;
      }
      else if (map[ballx - 1][bally + 1] == 1) stop = 2;//가려는 곳에 벽돌 존재
      else if (bally < 5) x--, ballx--, bally++;
      PrintMap();
      Sleep(10);
   }
   if (x == 0 && ballx >= 1 && map[ballx - 1][bally - 1] != 1)Left_up();//더 올라가야 하는데 오른쪽 벽끝에 위치해있음->왼쪽으로 방향전환
   else if (stop == 1) Move_down();//벽돌 깨고 내려감
   else if (stop == 2) {//가려는 곳에 벽돌이 있음
      if (x >= 1 && map[ballx - 1][bally - 1] != 1) Left_up();//더 올라갈수 있는데 왼쪽으로 가려고 할때 벽돌이 없음
      else UP();
   }
   else Down();
}
void Ball::Left_up() {
   int x, stop = 0;
   x = ballx;
   while (stop == 0 && x >= 1) {
      system("cls");
      if (bally == 0)x = 0;
      if (map[ballx - 1][bally] == 1) {
         map[ballx - 1][bally] = 0;
         brick--;
         stop = 1;
      }
      else if (map[ballx - 1][bally - 1] == 1)stop = 2;
      else if (bally > 0) x--, ballx--, bally--;
      PrintMap();
      Sleep(10);
   }
   if (x == 0 && ballx >= 1 && map[ballx - 1][bally + 1] != 1)Right_up();
   else if (stop == 1)Move_down();
   else if (stop == 2) {
      if (x >= 1 && map[ballx - 1][bally + 1] != 1)Right_up();
      else UP();
   }
   else Down();
}
void Ball::Down() {
   while (ballx <= 8) {
      system("cls");
      ballx++;
      PrintMap();
      Sleep(10);
      if (ballx == 9)time++;
   }
}
void Ball::Right_down() {//x,y둘다 증가
   int x;//임시 높이 좌표
   x = ballx;
   while (map[ballx + 1][bally + 1] != 1 && x <= 8) {//가려는 곳이 벽돌이 아니고 높이가 8보다 작을동안 반복
      system("cls");
      if (bally == 5) x = 9;//와이축이 오른쪽 끝일때 while문 탈출
      else  x++, ballx++, bally++;
      PrintMap();
      Sleep(10);
      if (ballx == 9)time++;
   }
   if (x == 9 && ballx <= 8) Left_down();//더 내려가야하는데 오른쪽벽에 부딪혔을때 왼쪽으로 방향 전환
   else if (x <= 8) {//더 내려가야하는데 중각에 벽돌 만나서 while문 탈출했을때
      if (map[ballx + 1][bally - 1] != 1 && bally >= 1) Left_down();//왼쪽으로 내려가는 길에 벽이 없을때
      else Down();
   }
}
void Ball::Left_down() {//x증가, y감소
   int x;//임시 높이 좌표
   x = ballx;
   while (map[ballx + 1][bally - 1] != 1 && x <= 8) {
      system("cls");
      if (bally == 0) x = 9;
      else  x++, ballx++, bally--;

      PrintMap();
      Sleep(10);
      if (ballx == 9)time++;
   }
   if (x == 9 && ballx <= 8) Right_down();
   else if (x <= 8) {
      if (map[ballx + 1][bally + 1] != 1 && bally <= 4) Right_down();
      else Down();
   }
}

int main()
{
   srand(time(NULL));
   Ball cli;
   cli.Soc_Cli();

}
