import socket


def main():
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

        buffer = []
        while bytes := client_socket.recv(1000):
            buffer.append(bytes.decode("utf-8"))

        print(f"Message received from client: {''.join(buffer)}")

        client_socket.close()

    s.close()

    # Alternative to the above:
    # with socket.create_server(('', 8000)) as server:
    #     while True:
    #         conn, addr = server.accept()

if __name__ == "__main__":
    main()