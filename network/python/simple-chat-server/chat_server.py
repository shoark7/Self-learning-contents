import select
import socket
import sys


HOST = 'localhost'
SOCKET_LIST = []
RECV_BUFFER = 4096
PORT = 8888


def broadcast(server_socket, sock, message):
    for socket_ in SOCKET_LIST:
        if socket_ not in (server_socket, sock):
            try:
                socket_.send(message)
            except:
                socket_.close()
                if socket_ in SOCKET_LIST:
                    SOCKET_LIST.remove(socket_)


def chat_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind((HOST, PORT))
    server_socket.listen(10)

    SOCKET_LIST.append(server_socket)
    print("Chat server started on port:", str(PORT))

    while True:
        ready_to_read, ready_to_write, in_error = select.select(SOCKET_LIST, [], [], 0)

        for sock in ready_to_read:
            if sock == server_socket:
                sock_fd, addr = server_socket.accept()
                SOCKET_LIST.append(sock_fd)
                print("Client {}: {} connected".format(*addr))
                broadcast(server_socket, sock_fd, "{}:{} entered our chatting room\n".format(*addr))
            else:
                try:
                    data = sock.recv(RECV_BUFFER)
                    if data:
                        broadcast(server_socket, sock, "\r" + '[' + str(sock.getpeername()) + '] ' + data)
                    else:
                        if sock in SOCKET_LIST:
                            SOCKET_LIST.remove(sock)
                            broadcast(server_socket, sock, "Client {}:{} is offline\n".format(*addr))
                except:
                    broadcast(server_socket, sock, "Client {}:{} is offline\n".format(*addr))
    server_socket.close()


if __name__ == '__main__':
    sys.exit(chat_server())
