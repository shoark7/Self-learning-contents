CC     = gcc
CFLAGS = -Wall -Wextra
TARGET = TCPEchoClient4

all: $(TARGET) 

$(TARGET): $(TARGET).o DieWithMessage.o
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c -o $@ $^

DieWithMessage.o: ../include/DieWithMessage.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf *.o $(TARGET)
