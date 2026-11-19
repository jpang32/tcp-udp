#include <fcntl.h>   // For open() and O_* flags
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_PORT 8000

/*
 * TODO: implement the server yourself.
 * Should create a TCP socket, bind it to `port`, listen, and accept/handle clients.
 * Return 0 on success, non-zero on failure.
 */
int run_server(int port)
{
    /* Placeholder so the program links. Replace with your socket code. */
    (void)port;

    // Tabling the creation of the file descriptor itself: right now, I am not sure
    // how to connect the raw socket to a file descriptor that I manage myself *without*
    // using the socket struct, which manages it for you. Can come back to this once I understand
    // more about how the OS internally manages file descriptors.
    // But AFAIK, the fd in this process maps to a global fd in a table that the OS manages.
    // Beyond that, I am not sure how the fd binds with the socket itself, or how subsequent communications are
    // routed to it.
    int fd = open("my_socket.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // SYS call 

    // When the client send()s a message, it is put into the clients send buffer, which is a data structure that exists
    // within the socket.

    // These packets are then sent, one by one, to the server. In the case of TCP, this request includes the sequence number
    // because TCP is an ordered connection.
    // The server, upon receiving a packet, will send an ack back to the client, which indicates that the packet was successfully received.
    // The packet is then written into the server socket's recv buffer.

    return 0;
}

int main(int argc, char *argv[])
{
    int port = DEFAULT_PORT;

    if (argc > 1) {
        port = atoi(argv[1]);
    }

    printf("Starting server on port %d\n", port);

    int status = run_server(port);
    if (status != 0) {
        fprintf(stderr, "Server exited with error %d\n", status);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
