#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <process.h>
#include <stdlib.h>
#include <time.h>

#pragma comment (lib, "ws2_32.lib")
#pragma warning(disable:4996)

using namespace std;

#define PORT   5500
#define BUFFERSIZE 100
#define NAMESIZE 30

unsigned  sendThread, receiveThread;
class THD {
public:
   int Soc_Cli();
   static unsigned __stdcall sendMessage(void* arg);
   static unsigned __stdcall receiveMessage(void *arg);
};

int THD::Soc_Cli()
{
   WSADATA wsadata;
   WSAStartup(MAKEWORD(2, 2), &wsadata);

   /*서버에 접속해서 메시지를 주고 받는 클라이언트 소켓생성*/
   int mySocket = socket(PF_INET, SOCK_STREAM, 0);
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
   char greetMessage[BUFFERSIZE];  //서버에서 전송할 환영 메시지를 저장할 배열
                           /*서버에서 전송한 환영 메시지를 읽어 들임*/
   recv(mySocket, greetMessage, sizeof(greetMessage), 0);
   cout << greetMessage << endl;
   /*키보드 입력을 읽어 들여서 서버로 전송하는 sendMessage 함수를 멀티 쓰레드로 시작함*/
   unsigned long hSendThread = _beginthreadex(NULL, 0, sendMessage, (void*)mySocket, 0, &sendThread);
   /*서버에서 전송한 다른 클라이언트들의 메시지를 읽어 들여서 화면에 출력하는 receiveMessage 함수를 멀티 쓰레드로 시작함*/
   unsigned long hReceiveThread = _beginthreadex(NULL, 0, receiveMessage, (void*)mySocket, 0, &receiveThread);

   /*sendMessage 함수를 멀티 쓰레드로 실행하는 sendThread 가 종료 할때 까지 main 함수가 대기 하도록 함*/
   WaitForSingleObject((HANDLE)hSendThread, INFINITE);
   /*receiveMessage 함수를 멀티 쓰레드로 실행하는 receiveThread 가 종료 할때 까지 main 함수가 대기 하도록 함*/
   WaitForSingleObject((HANDLE)hReceiveThread, INFINITE);
}
unsigned __stdcall THD::sendMessage(void* arg)
{
   /*서버와 데이터를 주고 받는 클라이언트 소켓을  멀티 쓰레드 시작시 main 함수에서 인자로 전달 받습니다. 인자로 전달 받은 클라이언트 소켓을 mySocket 에 대입합니다. */
   int mySocket = (int)arg;
   char fromClientInput[BUFFERSIZE]; // 키보드 입력을 저장할 배열
   char myName[NAMESIZE]; //클라이언트 대화명을 저장할 배열
                     /*대화명과 키보드 입력내용을 하나로 묶어서 서버로 보낼 메시지를 저장할 배열*/
   char toServer[NAMESIZE + BUFFERSIZE];
   cout << "채팅을 시작합니다." << endl;
   cout << "클라이언트의 대화명을 입력하세요 -->";
   fgets(myName, NAMESIZE, stdin); //입력 받은 대화명을 myName 에 대입
   myName[strlen(myName) - 1] = '\0'; //대화명 맨 끝에 NULL 문자를 추가
                              /*“대화명 님이 입장하셨습니다.” 라는 메시지를 toServer 배열에 대입*/
   sprintf(toServer, "[%s] 님이  입장 하셨습니다", myName);
   /*“대화명 님이 입장하셨습니다” 라는 toServer 배열에 저장된 메시지를 서버로 전송*/
   send(mySocket, toServer, sizeof(toServer), 0);
   while (1) {
      /*키보드 입력을 읽어 들여서 fromClientInput 배열에 대입*/
      fgets(fromClientInput, BUFFERSIZE, stdin);
      /*myName 에 대입된 대화명과 fromClient 에 대입된 키보드 입력을 하나로 묶어서 toServer 배열에 대입*/
      sprintf(toServer, "[%s] %s", myName, fromClientInput);
      toServer[strlen(toServer) - 1] = '\0'; // toServer 배열 맨 마지막에 NULL 문자를 대입
      send(mySocket, toServer, sizeof(toServer), 0); // toServer 배열에 저장된 메시지를 서버로 전송

                                          /*키보드 입력이 “quit" 이면  ”대화명 님이 나가셨습니다“ 라는 메시지를 서버로 전송하고 서버와의
                                          연결을 종료함*/
      if (strcmp(strlwr(fromClientInput), "quit\n") == 0) {
         sprintf(toServer, "[%s] 님이 나가셨습니다.", myName);
         send(mySocket, toServer, sizeof(toServer), 0);
         cout << "프로그램을 종료합니다." << endl;
         closesocket(mySocket);
         break;
      } // if
   }  // while
   return 0;
}
unsigned __stdcall THD::receiveMessage(void *arg)
{
   int mySocket = (int)arg; // main 함수로부터 전달받은 클라이언트 소켓을 mySocket 에 대입
   int strlen = 0; // 서버에서 전달한 메시지의 바이트 수를 대입할 변수*/
               /*서버에서 전달한 메시지를 저장할 변수. 서버에서는 메시지를 입력한 클라이언트의 대화명과 클라이언트의
               메시지가 하나로 묶여서 전달됨*/
   char fromServer[NAMESIZE + BUFFERSIZE];
   while (1) {
      /*서버에서 메시지를 읽어 들여서 frmServer 에 대입함*/
      strlen = recv(mySocket, fromServer, sizeof(fromServer), 0);
      /*strlen 이 0인 경우는 서버 소켓이 종료 되었을때 이므로 이때는 함수를 종료함. 함수를 종료 하면 receiveMessage 함수를 실행하는 쓰레드도 종료됨*/
      if (strlen <= 0) break;
      /*서버로부터 전달 받은 메시지를 화면에 출력함*/
      cout << fromServer << endl;

   }  // while
   return 0;
}
int main()
{
   THD cli;

   cli.Soc_Cli();
}
