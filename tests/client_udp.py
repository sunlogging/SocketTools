import socket

# создаем сокет
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# адрес и порт сервера
server_address = ('localhost', 9096)

# отправляем сообщение
message = b'Hello, world!'
sock.sendto(message, server_address)

# получаем ответ
data, server = sock.recvfrom(4096)
print(data)

# закрываем сокет
sock.close()