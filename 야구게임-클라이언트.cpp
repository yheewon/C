#include <winsock2.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>


#define PORT   5500 /*서버와 클라이언트간에 데이터를 주고 받을 포트번호*/
#define    BUFFER_SIZE    100 

#pragma comment (lib, "ws2_32.lib") //ws2_32.lib 라이브러리 링크
#pragma warning(disable:4996)

using namespace std;
class SOC {
private:
   WSADATA wsdata;
   SOCKET clientSocket; /* 서버에 접속할 클라이언트 소켓 변수 선언*/
   SOCKADDR_IN serverAddress; /* 서버소켓의 주소정보를 저장 하는 구조체 변수 선언 */
   int clientNumber[3];  // 클라이언트에서 입력할 세 개의 수
   int i;
   int score[2];//서버에서 전달된 스크라익과 볼의 개수를 저장할 배열

public:
   int Cli_Start();
};
int SOC::Cli_Start()
{
   /*WS_32.DLL 을 초기화 */
   if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
      cout << "WS2_32.DLL 을 초기화 하는데 실패했습니다. " << endl;
      return 0;
   }

   cout << "WS_32.DLL 을 초기화 하는데 성공 했습니다 " << endl;
   /*socket 함수를 이용해서 clientSocket을 생성 */
   clientSocket = socket(AF_INET, SOCK_STREAM, 0);
   ZeroMemory(&serverAddress, sizeof(serverAddress));

   /* serverAddress 에 필요한 주소 정보를 저장 합니다.*/
   serverAddress.sin_family = AF_INET; /*소켓의 주소 체계를 설정 합니다.       TCP/IP 프로토콜의 경우 인터넷 기반이므로 AF_INET 을 대입합니다.*/
   serverAddress.sin_port = htons(PORT); /*서버 소켓의 포트를 설정 합니다.  */
   serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");/*서버의 IP를 설정 합니다.*/
                                             /*serverAddress에 저장된 서버의 정보를 이용해서 서버에 접속합니다.*/
   if ((connect(clientSocket, (SOCKADDR *)(&serverAddress), sizeof(serverAddress)) != 0))
   {
      cout << "서버에 접속하는데 실패 했습니다 " << endl;
      return 0;
   }
   cout << "서버에 접속 했습니다 " << endl;
   cout << "야구 게임을 시작합니다. " << endl;
   while (1) {//스트라익이 3이될때 까지 반복
      cout << "세 수를 입력해 주세요(ex: 1 2 3)\n-->" << endl;
      /*키보드 입력된 세개의 숫자를 읽어 들임*/
      cin >> clientNumber[0] >> clientNumber[1] >> clientNumber[2];

      /*데이터를 전송하기 위해서 네트워크 바이트 정렬 방식으로 데이터 정렬*/
      for (i = 0; i < 3; i++)
         clientNumber[i] = htonl(clientNumber[i]);

      /*입력된 세개의 숫자 서버로 전송*/
      send(clientSocket, (char *)clientNumber, sizeof(clientNumber), 0);

      recv(clientSocket, (char*)score, sizeof(score), 0);//서버에서 전달한 스트라익과 볼의 개수를 읽어 들임
                                             //네트워크 바이트 정렬된 데이터를 호스트 바이트 정렬한후에 스트라익과 볼에 대입
      int strike = ntohl(score[0]);
      int ball = ntohl(score[1]);
      cout << strike << " 스트라이크 " << ball << " 볼 " << endl;
      /*스트라익이 3이면 프로그램 종료*/
      if (strike == 3) {
         cout << " 3 스트라이크 프로그램을 종료 합니다. " << endl;
         break;
      }  // end if
   } // end while   
     /*서버와의 연결을 종료합니다.*/
   closesocket(clientSocket);
   /*WS_32.DLL 사용을 종료 합니다.*/
   WSACleanup();
   cout << "클라이언트를 종료합니다 " << endl;

   return 0;
}

int main()
{
   SOC cli;

   cli.Cli_Start();
}
