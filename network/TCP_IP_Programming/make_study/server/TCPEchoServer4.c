#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../include/Practical.h"

static const int MAXPENDING = 5;	// 연결 요청을 대기할 수 있는 최대수

int main(int argc, char *argv[]){

	if(argc != 2) // 명령어 인자의 개수 확인
		DieWithUserMessage("Parameter(s)", "<Server Port>");

	in_port_t servPort = atoi(argv[1]); // 첫 번째 인자: 지역 포트

	// 연결 요청을 처리하는 소켓 생성
	int servSock;	// 서버 소켓 식별자
	if((servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		DieWithSystemMessage("socket() failed");
	
	// 지역 주소 구조체 생성
	struct sockaddr_in servAddr;					// 지역 주소
	memset(&servAddr, 0, sizeof(servAddr));			// 0으로 구조체 초기화
	servAddr.sin_family = AF_INET;					// IPv4 주소 패밀리
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);	// 호스트의 어떠한 IP로도 연결 요청 수락
	servAddr.sin_port = htons(servPort);			// 지역 포트

	// 지역 주소에 바인드
	if(bind(servSock, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0)
		DieWithSystemMessage("bind() failed");
	
	if(listen(servSock, MAXPENDING) < 0)
		DieWithSystemMessage("listen() failed");

	for(;;){ // 무한 실행
		struct sockaddr_in clntAddr; // 클라이언트 주소
		// 클라이언트 주소 구조체 크기 설정
		socklen_t clntAddrLen = sizeof(clntAddr);

		// 클라이언트의 연결을 기다린다.
		int clntSock = accept(servSock, (struct sockaddr *) &clntAddr, &clntAddrLen);
		if(clntSock < 0)
			DieWithSystemMessage("accept() failed");

		// clntSock이 클라이언트와 연결되었다.

		char clntName[INET_ADDRSTRLEN];	// 클라이언트 주소를 담기 위한 문자열
		if(inet_ntop(AF_INET, &clntAddr.sin_addr.s_addr, clntName,
		   sizeof(clntName)) != NULL)
			printf("Handling client %s/%d\n", clntName, ntohs(clntAddr.sin_port));
		else
			puts("Unable to get client address");

		HandleTCPClient(clntSock);
	}
}
