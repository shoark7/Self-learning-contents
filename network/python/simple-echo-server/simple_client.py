from socket import gethostname, socket, AF_INET, SOCK_STREAM


host = gethostname()
port = 9999

while True:
    client_socket = socket(AF_INET, SOCK_STREAM)
    client_socket.connect((host, port))
    message = input("")
    if message == 'quit':
        break
    client_socket.send(message.encode('utf-8'))
    tm = client_socket.recv(1024)
    print(tm.decode('utf-8'))
    client_socket.close()
