#include <fcntl.h>   // For open() and O_* flags
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#define PORT_NO "8000"

/*
 * TODO: implement the server yourself.
 * Should create a TCP socket, bind it to `port`, listen, and accept/handle clients.
 * Return 0 on success, non-zero on failure.
 */
int run_server()
{
    /* Placeholder so the program links. Replace with your socket code. */

    // Tabling the creation of the file descriptor itself: right now, I am not sure
    // how to connect the raw socket to a file descriptor that I manage myself *without*
    // using the socket struct, which manages it for you. Can come back to this once I understand
    // more about how the OS internally manages file descriptors.
    // But AFAIK, the fd in this process maps to a global fd in a table that the OS manages.
    // Beyond that, I am not sure how the fd binds with the socket itself, or how subsequent communications are
    // routed to it.
    // int fd = open("my_socket.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // We need to use a protocol that allows us to send and receive
    // If we use protocl 255, IPPROTO_RAW, that lets us send things, 
    // but blocks us from receiving. We need both on the server socket.
    // int raw_socket = socket(PF_INET, SOCK_RAW, 253);
    
    // Import the addr_info struct (do you even need to import?)
    // Get the size of such a struct

    // This is what's happening: I don't really understand C structs
    // My point is to allocate space for my pointer, of size addrinfo so that it is able to fit it
    // Particularly, I thnk you can assign what malloc returns to the addr info pointer you have, something like:
    printf("test\n");

    // Variables which are not malloc'd will be forgotten after leaving scope. They
    // are popped off of the stack as soon as the scope is left.
    // On the another hand, variables which are malloc'd, and created on the heap, stay
    // allocated until one manually frees them from the heap.
    
    // Allocate memory for the addrinfo structs.
    // Not strictly necessary, but good for understanding memory allocation

    // Specifically, memory allocation is useful for persisting data across scope,
    // by allocating outside of the stack, the variable still exists even after 
    // the function returns, which would instead be popped off the stack.
    struct addrinfo *addr_info = calloc(1, sizeof(struct addrinfo));
    struct addrinfo *res = calloc(1, sizeof(struct addrinfo));
    
    // 1. Family PF_INET: this says that we will use
    // ipv4, and tells us the "family", or group, of related protocols that are allowed
    // for use with internet version 4.

    // 2. Socket type SOCK_RAW: Setting up the socket such that the kernel does not 
    // automatically handle TCP / UDP operations.
    // More is needed to understand this, but at a basic level, you would be implementing
    // the second and third layers of the internet

    // Casting the point to a struct is necessary: calloc returns void pointer,
    // which subsequent methods cannot interpret correctly without it being
    // explicitly cast to struct addrinfo
    *addr_info = (struct addrinfo) {
        .ai_family = PF_INET, 
        .ai_socktype = SOCK_RAW
    };

    // 
    int c = getaddrinfo("127.0.0.1", PORT_NO, addr_info, &res);
    if (c != 0) {
        printf("Error creating address info: %d\n", c);
        return EXIT_FAILURE;
    } else {
        printf("Successfully creating addrinfo\n");
    }

    printf("addrlen: %d\n", res->ai_addrlen);
    printf("addr_info ipv4: %s\n", res->ai_addr->sa_data);
    printf("addr_info ipv6: %s\n", res->ai_next->ai_addr->sa_data);

    // AF_INET, SOCKET_RAW, ??
    int raw_socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    printf("socket: %d\n", raw_socket);

    if (bind(raw_socket, res->ai_addr, res->ai_addrlen) != 0) {
        printf("Error binding socket to address: %d\n", c);
        return EXIT_FAILURE;
    } else {
        printf("Successfully bound socket to address\n");
    }

    if (bind(raw_socket, res->ai_addr, res->ai_addrlen) != 0) {
        printf("Error binding socket to address: %d\n", c);
        return EXIT_FAILURE;
    } else {
        printf("Successfully bound socket to address\n");
    }

    while()

    // If you want, next time you come around to this: let's jump to the section on
    // binding and listening, and then we can go forward with the protocol implementation

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


    printf("Starting server on port %s\n", PORT_NO);

    int status = run_server();
    if (status != 0) {
        fprintf(stderr, "Server exited with error %d\n", status);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
