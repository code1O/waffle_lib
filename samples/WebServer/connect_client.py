import socket
from socket import (AddressFamily, SocketType)

class sockaddr_in:
    sin_family: AddressFamily
    sin_type: SocketType
    sin_addr_saddr: str
    
    # Additional components
    sin_port: int

ClientSocket = ...

def init_data():
    sockaddr_in.sin_family = socket.AF_INET
    sockaddr_in.sin_type = socket.SOCK_STREAM
    sockaddr_in.sin_port = 8080
    sockaddr_in.sin_addr_saddr = "127.0.0.1"

def make_client():
    init_data()
    ClientSocket = socket.socket(sockaddr_in.sin_family, sockaddr_in.sin_type)

def run_forever():
    while 0x01:
        ClientSocket.connect(sockaddr_in.sin_addr_saddr)
    ClientSocket.close()


# INITIALIZE CLIENT CONNECTION


if __name__ == "__main__":
    make_client()
    run_forever()



