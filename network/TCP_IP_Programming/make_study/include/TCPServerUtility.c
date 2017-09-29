#include <sys/types.h>
#include <sys/socket.h>
#include "Practical.h"

#define BUFSIZE 512

void HandleTCPClient(int clntSocket)
{
	char buffer[BUFSIZE]; // 에코 문자열을 위한 버퍼

	// 클라이언트로부터 메시지를 수신
	ssize_t numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);
	if(numBytesRcvd < 0)
		DieWithSystemMessage("recv() failed");

	// 수신한 문자열을 전송하고 여분의 데이터를 스트림이 끝날 때까지 수신
	while(numBytesRcvd > 0) { // 0일 경우 스트림의 종료를 의미한다.
		// 클라이언트 에코 메시지를 돌려보낸다.
		ssize_t numBytesSent = send(clntSocket, buffer, numBytesRcvd, 0);
		if(numBytesSent < 0)
			DieWithSystemMessage("send() failed");
		else if(numBytesRcvd != numBytesSent)
			DieWithUserMessage("send()", "sent nuexpected number of bytes");

		// 받을 수 있는 데이터가 더 남아있는지 확인한다.
		numBytesRcvd = recv(clntSocket, buffer, BUFSIZE, 0);
		if(numBytesRcvd < 0)
			DieWithSystemMessage("recv() failed");
	}

	close(clntSocket); // 클라이언트 소켓 종료
}

