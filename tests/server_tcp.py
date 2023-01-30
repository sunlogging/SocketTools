import socket

SERVER_ADDRESS = ('localhost', 8686)

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(SERVER_ADDRESS)
server_socket.listen(3)

print('run')

while True:
    connection, address = server_socket.accept()

    print(f"connect from {address}")
    print(str(connection.recv(1024)))

    connection.send(bytes('TEST SEND BYTES', encoding='UTF-8'))

    connection.close()