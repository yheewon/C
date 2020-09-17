#include <winsock2.h> /*소켓 통신에 필요한 함수 들이 선언되어있는 헤더파일 */////////////////////
#include <iostream>
#include <stdlib.h>
#include <time.h>


#define PORT   5500 /*서버와 클라이언트간에 데이터를 주고 받을 포트번호*////////////////////////////////////////
#define    BUFFER_SIZE    100 /////////////////////////////////////////////////////

#pragma comment (lib, "ws2_32.lib") //ws2_32.lib 라이브러리 링크//////////////////////////////////////////////
#pragma warning(disable:4996)///////////////////////////////////////////////////////////

using namespace std;
class SOC {
private:
   /*윈도우 소켓 초기화*/
   WSADATA wsdata;////////////////////////////////////////////////////////////
   /*서버의 주소를 저장하는 구조체 serverAddress 생성*/
   sockaddr_in serverAddress;/////////////////////////////////////////////////////
   /*서버쪽 숫자를 저장할 배열선언*/
   int serverNumber[3];
   int fromClientNumber[3]; //클라이언트가 입력한 세 개의 숫자를 대입할 배열
   int toClientScore[2];//스트라익과 볼의 개수를 저장해서 클라이언트로 전송할 배열
   int index;
   SOCKET servsoc;
   SOCKET clisoc;
   int strike;//스트라익의 수를 대입할 변수
   int ball;//볼의 수를 대입할 변수

public:
   int Ser_Start();
};
int SOC::Ser_Start()
{
   int i;

   if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
      cout << "WS2_32.DLL 을 초기화 하는데 실패했습니다. " << endl;
      return 0;
   }
   cout << "WS_32.DLL 을 초기화 하는데 성공 했습니다 " << endl;

   servsoc = socket(AF_INET, SOCK_STREAM, 0);
   cout << "서버 소켓을 생성 했습니다. " << endl;


   /*ZeroMemory 함수는 해당 메모리를 0으로 초기화 시켜주는 함수.
   serverAddress 배열을 0으로 초기화. */
   ZeroMemory(&serverAddress, sizeof(serverAddress));
   serverAddress.sin_family = AF_INET; /*소켓의 주소 체계를 설정.
                              TCP/IP 프로토콜의 경우 인터넷 기반이므로 AF_INET 을 대입.*/

   serverAddress.sin_port = htons(PORT); /*서버 소켓의 포트를 설정*/
   serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);/*서버의 IP를 설정 */

   if (bind(servsoc, (SOCKADDR *)&serverAddress,
      sizeof(serverAddress)) == SOCKET_ERROR)
   {
      cout << "serverSocket에 IP 와 PORT 를 부여 하는데 실패했습니다! " << endl;
      return 0;
   }
   cout << "serverSocket 에 IP 와 Port 를 부여 하는데 성공 했습니다 " << endl;
   cout << "클라이언트의 접속을 감시 합니다 " << endl;
   listen(servsoc, 5);

   /*클라이언트가 서버에 접속하면 accept 함수 호출.
   accept 함수는 클라이언트의 접속을 허락하고 클라이언트와 데이터를 주
   고 받는 일을 전담하는 socket을 리턴*/

   if ((clisoc = accept(servsoc, NULL, NULL)) == INVALID_SOCKET)
   {
      cout << "클라이언트와 데이터를 주고 받는 socket을 생성 할 수 없습니다." << endl;
      return 0;
   }
   cout << " 클라이언트가 접속 했습니다 " << endl;
   cout << " 야구 게임 시작... " << endl;

   /*난수를 생성하기 위한 초기화*/
   srand((unsigned)time(NULL));
   do {
      /*난수를 생성하고 난수를 10으로 나눈 나머지를 대입*/
      serverNumber[0] = rand() % 10;
      serverNumber[1] = rand() % 10;
      serverNumber[2] = rand() % 10;
   }
   /*배열에 같은 수가 없을때 까지 반복함*/
   while ((serverNumber[0] == serverNumber[1]) |
      (serverNumber[1] == serverNumber[2]) |
      (serverNumber[2] == serverNumber[0]));

   cout << " 서버 숫자 --> " << serverNumber[0] << serverNumber[1] <<
      serverNumber[2] << endl;
   while (1) {
      /*클라이언트가 입력한 세개의 숫자를 읽어 들여서 fromClientNumber 에 대입함*/
      recv(clisoc, (char*)fromClientNumber, sizeof(fromClientNumber), 0);
      strike = ball = 0;

      /*네트워크 바이트 정렬된 숫자를 호스트 바이트로 재정렬*/
      for (index = 0; index<3; index++)
         fromClientNumber[index] = ntohl(fromClientNumber[index]);
      /*클라이언트가 입력한 수를 출력*/
      cout << " 클라이언트가 입력한 수 --> " << fromClientNumber[0]
         << fromClientNumber[1] << fromClientNumber[2] << endl;
      for (i = 0; i<3; i++) {
         /*서버의 숫자가 저장된 serverNumber 에서 i번째 숫자를 꺼내서 oneServerNumber 에 대입*/
         int oneServerNumber = serverNumber[i];
         for (int j = 0; j<3; j++) {
            /*클라이언트에서 전송한 숫자가 저장된 fromClientNumber 의 j번째 숫자를 꺼내서 oneClientNumber 에 대입*/
            int oneClientNumber = fromClientNumber[j];
            /*서버의 숫자와 클라이언트의 숫자가 같으면*/
            if (oneServerNumber == oneClientNumber) {
               /*서버 숫자의 위치와 클라이언트 숫자의 위치가 같으면*/
               if (i == j) strike++; //스트라익 1증가
               else ball++;//숫자는 같으나 위치는 틀리면 볼 1증가
            }//end if
         }//end for(j)
      }//end for(i)
      cout << strike << "스트라이크" << ball << "볼" << endl;
      /*스트라익과 볼의 개수를 클라이언트로 전송하기 위해서 네트워크 바이트로 정렬하고 toClientScore 배열에 대입*/
      toClientScore[0] = htonl(strike);
      toClientScore[1] = htonl(ball);
      /*클라이언트로 스트라익개수와 볼의 개수 전송*/
      send(clisoc, (char*)toClientScore, sizeof(toClientScore), 0);//<--수정된 부분
                                                    /*세개의 숫자의 위치와 수를 모두 맞춰서 스트라익이 3이면 개임 종료 */
      if (strike == 3) {
         cout << " 3 스트라이크 프로그램을 종료 합니다. " << endl;
         break;//while 반복문 종료
      }
   } // end while 
     /*클라이언트와의 연결을 종료합니다.*/
   closesocket(servsoc);
   cout << "클라이언트와의 접속을 종료 했습니다 " << endl;
   /*WS_32.DLL 사용을 종료 합니다.*/
   WSACleanup();
   cout << "서버를 종료합니다 " << endl;

   return 0;
}

int main()
{
   SOC ser;

   ser.Ser_Start();
}
