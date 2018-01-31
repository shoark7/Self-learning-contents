#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9000

char buffer[BUFSIZ] = "hello, world\n";

int main()
{
	// c는 client의 약자, s는 server의 약자.
	int c_socket, s_socket;
	struct sockaddr_in s_addr, c_addr;
	int len;
	int n;

	s_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 버클리 소켓 관련 구조체들은 항상 쓰기전에 memset()을 해줘야 한다.
	// 여기서 sin_family는 IP주소를 뜻한다. 그리고 IP주소로 INADDR_ANY를 설정한 이유는 
	// 한 컴퓨터에 여러 장의 LAN 카드가 장착되어 있어서 여러 개의 IP주소가 할당되고, 
	// 서버 응용 프로그램은 이들 IP를 통해 들어오는 모든 연결 요청을 받아 처리하기에 사용한 것이다.
	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(PORT);

	// 소켓을 포트에 연결한다. 참고로 bind(), accept(), listen()은 서버측에서만 사용하는 소켓 API다.
	// bind의 프로토타입은 다음과 같다. int bind(int sockfd, struct sockaddr *localAddress, socklen_t addressSize)
	// 클라이언트와 서버는 서버의 주소와 포트 번호에서 랑데뷰한다. 이것이 가능하려면 서버(프로그램)는 먼저 bind()를 통해 해당 주소와 포트를 소켓에 연결해야 한다.
	// 다시 말하지만 클라이언트는 connect()로 랑데뷰 포인트인 서버의 주소를 제공해야 하고, 서버는 bind()로 서버 자신의 주소를 명시해야 한다.
	// 즉, bind()는 서버 프로그램이 자신의 주소(IP주소, 포트 주소)를 명시하기 위해 사용하는 함수다.

	// 첫번째 인자는 IP주소와 포트 주소에 연결할 소켓을 넘기면 된다. 서버 소켓이 그 역할을 맡을 것이다.
	// 두번째 인자는 IP주소와 포트 주소가 담겨있는 s_addr구조체의 주소를 넘기면 된다. 
	// 세번째 인자는 두 번째 인자로 넘겨진 구조체의 크기를 명시하면 된다.
	if(bind(s_socket, (struct sockaddr *) &s_addr, sizeof(s_addr)) == -1) {
		printf("Can not Bind\n");
		return -1;
	}

	// listen()은 두가지 의미를 가지고 있다. 하나씩 알아보자.
	// 1. 커널에 개통을 요청한다: listen()이 성공적으로 호출된 시점부터 해당 소켓으로 통신이 이루어지도록 운영체제(커널)에 개통을 요청하고 있다.
	// 운영체제는 이 시점부터 다른 호스트에서 포트 번호 9000번으로 요청하는 연결을 받아들이기 시작한다.
	// 2. 랑데뷰 소켓을 s_socket으로 설정한다: 당신은 listen()에 넘겨진 socket이 다른 호스트의 모든 연결을 감당한다고 생각하는가?
	// 답은 '아니오'다. listen()에 넘겨진 소켓은 랑데뷰 소켓이 된다. 즉, 서버와 클라이언트가 만나는 지점일 뿐이지 네트워크 자원을 공급하고 공급받는 소켓이 아니라는 뜻이다.
	// 랑데뷰 소켓은 연결요청을 받아서 새로운 소켓(이를 커뮤니케이션 소켓이라 한다.)을 만들고, 연결 요청을 한 호스트에 이 커뮤니케이션 소켓을 연결해준다.
	// 주의하자!
	if(listen(s_socket, 5) == -1) {
		printf("listen Fail\n");
		return -1;
	}

	for(;;) {
		// 클라이언트로부터의 연결 요청을 수신한다. 58~59번 줄은 클라이언트로부터 연결 요청을 받아들이는 코드다.
		// 이를 위해서 accept()를 사용하게 되는데, 이 함수의 목적과 프로토타입을 알아보자.
		// int accept(int socket, struct sockaddr *clientAddress, socklen_t *addressLength)
		// 이 함수를 호출하면 큐(queue)에 대기하고 있는 다음 연결(socket)을 꺼낸다. 만약 큐가 비어 있으면 accept()는 연결 요청이 들어올 때까지 멈추어 있게(블로킹)된다. 
		// 성공 시 accept()는 clientAddress가 가리키는 sockaddr 구조체를 연결 상대인 클라이언트의 주소와 포트로 채운다. 
		// 저지르기 쉬운 실수로, addressLength가 가리키는 정수를 초기화하여 clientAddress가 가리키는 구조체의 크기를 확보하는 것을 실패하는 것이다.
		len = sizeof(c_addr);
		c_socket = accept(s_socket, (struct sockaddr *) &c_addr, &len);

		// 클라이언트에게 서비스를 제공한다.
		// 클라이언트와 연결된 연결 소켓(c_socket)으로 문자열 hello, world를 보낸다. 연결 소켓인 c_socket으로 hello, world라고 말하는 단계이다.
		// C 프로그램의 printf("hello, world");에 대응되며, 자신의 화면이 아닌 네트워크상의 클라이언트에 전송하게 된다.
		n = strlen(buffer);
		write(c_socket, buffer, n); // 시스템 콜 write가 맞다!

		// 클라이언트와의 연결을 종료한다.
		close(c_socket);
	}
	// 서버를 종료한다.
	close(s_socket);
}
