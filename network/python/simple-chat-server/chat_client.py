import select
import socket
import sys


def chat_client():
    if len(sys.argv) < 3:
        print("Usage: python chat_client.py hostname port")

    host, port = sys.argv[1:3]
    print('host is', host, 'port is', port)
    port = int(port)
    s = socket.socket()
    s.settimeout(2)

    try:
        s.connect((host, port))
    except:
        print("Unable to connect")
        sys.exit()

    print("connected to remote host. You can start sending messages")
    sys.stdout.write('[Me] ')
    sys.stdout.flush()

    while True:
        socket_list = [sys.stdin, s]

        to_read, to_write, to_error = select.select(socket_list, [], [])

        for sock in to_read:
            if sock == s:
                data = sock.recv(4096)
                print(data)
                if not data:
                    print("Disconnected from chat server")
                    sys.exit()
                else:
                    sys.stdout.write(data)
                    sys.stdout.write('[Me] ')
                    sys.stdout.flush()
            else:
                msg = sys.stdin.readline()
                s.send(msg.encode())
                sys.stdout.write('[Me] ')
                sys.stdout.flush()


if __name__ == '__main__':
    sys.exit(chat_client())
