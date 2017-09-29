# 매크로: 매크로 설정은 =으로 한다. 매크로의 이름은 C언어에서와 마찬가지로 전부 대문자로 통일하자.
# 매크로를 다음줄로 계속 이어서 하고 싶다면 /으로 계속 이을 수 있다. 설정한 매크로를 치환하고 싶다면 $(NAME)구문을 사용하자.
CC     = gcc
CFLAGS = -Wall -Wextra
TARGET = TCPEchoServer4

all: $(TARGET)

$(TARGET) : TCPEchoServer4.o DieWithMessage.o TCPServerUtility.o
	$(CC) $(CFLAGS) -o $@ $^

TCPEchoServer4.o : TCPEchoServer4.c
	$(CC) $(CFLAGS) -c -o $@ $^

DieWithMessage.o : ../include/DieWithMessage.c
	$(CC) $(CFLAGS) -c -o $@ $^

TCPServerUtility.o : ../include/TCPServerUtility.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean : 
	rm -rf *.o $(TARGET)
