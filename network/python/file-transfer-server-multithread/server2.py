import socket
from socketserver import ThreadingMixIn
from threading import Thread


TCP_IP = 'localhost'
TCP_PORT = 9001
BUFFER_SIZE = 1024


class ClientThread(Thread):

    def __init__(self, ip, port, sock):
        # Thread.__init__(self)
        super().__init__(target=self)
        self.ip = ip
        self.port = port
        self.sock = sock
        print("New thread started for", ip)

    def run(self):
        filename = 'mytext.txt'
        f = open(filename, 'rb')
        while True:
            l = f.read(BUFFER_SIZE)
            while l:
                self.sock.send(l)
                l = f.read(BUFFER_SIZE)
            f.close()
            self.sock.close()
            break


tcp_sock = socket.socket()
tcp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
tcp_sock.bind((TCP_IP, TCP_PORT))
threads = []

while True:
    tcp_sock.listen(5)
    print("Waiting for incoming connections...")
    (conn, (ip, port)) = tcp_sock.accept()
    new_thread = ClientThread(ip, port, conn)
    new_thread.start()
    threads.append(new_thread)

for t in threads:
    t.join()
