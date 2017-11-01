import socket
import time


TCP_IP = 'localhost'
TCP_PORT = 9001
BUFFER_SIZE = 1024

s = socket.socket()
s.connect((TCP_IP, TCP_PORT))


clock_start = time.clock()
time_start = time.time()

with open('received_file', 'wb') as f:
    print('File opened!')
    while True:
        data = s.recv(1024)
        if not data:
            break
        f.write(data)

s.close()
clock_end = time.clock()
time_end = time.time()

duration_clock = clock_end - clock_start
duration_time = time_end - time_start
print('duratio clock:', duration_clock)
print('duratio time:', duration_time)
