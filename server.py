import socket
from socket import AF_INET, SO_LINGER, SOCK_STREAM, SOL_SOCKET
import os


def create_server_with_os():
    """ This function re-creates the process of opening a socket and reading a TCP / UDP connection by 
    mimicing what happens at the hardware level, implementing the various data structures that are used 
    at the kernel level.

    The goal of writing this function is to get a better understanding of what happens underneath the hood,
    before we move over to C and start making system calls.
    """

    # 1. Opens a file descriptor from the table of file descriptors that belong to this process
    # 2. Maps that fd to a specific system-level table mapped to by the kernel
    fd = os.open("my_socket.txt", os.O_RDWR | os.O_CREAT)

    # "Assign" file descriptor to the localhost, as well as a paritcular port
    # "Listen" for incoming connections, which includes adding new connections to a connections queue

    # Some lower-level things to explore:
    # 1. Do we need the operating system to create all aspects of the socket? Or can we access those socket resources via
    # code and create them ourselves?
    # 2. How does one link the fd to the socket via code?
    # 3. How does one bind the socket to the fd via code?
    # 4. How do you listen to incoming connections via code?
    # 5. How do you put incoming connections on the connections queue?
    # 6. How do you pop connections from that queue, and open up the new socket to listen for data coming
    


    s = socket.socket(family=AF_INET, type=SOCK_STREAM, proto=0, fileno=fd)


    s.bind('', 8000)

    



def create_server_with_socket():
    # Create server to listen on specific port
    # Might require some sort of binding
    # Create a callback such that the server, when it receives something,
    # reads in a certain limit of the characters which come in
        # This part requires taking the UDP / TCP packets and decoding the information

    # Create client
    # Send messages to specific port, with size limit
        # This part requires taking the data and encoding it into UDP / TCP packets

    # Defaults to type SOCK_STREAM
    s = socket.socket()

    # Binds the file descriptor to the address / port
    s.bind(('', 8000))
    # Listen for new connections: when a new one comes in, the OS
    # will put that connection on a queue
    s.listen()

    while True:
        # Pop off the latest connection from the queue
        print("Waiting for client:")
        client_socket, _ = s.accept()

        client_socket.setsockopt(SOL_SOCKET, SO_LINGER, 5)

        buffer = []
        while bytes := client_socket.recv(1000):
            buffer.append(bytes.decode("utf-8"))

        print(f"Message received from client: {''.join(buffer)}")

        print("Test")
        client_socket.close()
        print("test2")

    s.close()

    # Alternative to the above:
    # with socket.create_server(('', 8000)) as server:
    #     while True:
    #         conn, addr = server.accept()

if __name__ == "__main__":
    create_server_with_socket()