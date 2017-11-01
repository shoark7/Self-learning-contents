from socket import gethostname, socket, AF_INET, SOCK_STREAM


server_socket = socket(AF_INET, SOCK_STREAM)
host = gethostname()
port = 9999

server_socket.bind((host, port))
server_socket.listen(5)

while True:
    client_socket, addr = server_socket.accept()
    message = client_socket.recv(1024)
    client_socket.send(message)
    client_socket.close()
