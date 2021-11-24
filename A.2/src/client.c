#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <client.h>
#include <common.h>

void parse_args(int argc, char**argv, char* ip_address, int* port) {
    strcpy(ip_address, "127.0.0.1");
    *port = 5050;
    int opt;
    debug(LINE);
    while ((opt = getopt(argc, argv, "a:p:")) != -1) {
        switch (opt)
        {
        case 'a':
            strcpy(ip_address, optarg);
            debug("IPv4: %s\n", ip_address);
            break;
        case 'p':
            *port = atoi(optarg);
            debug("PORT: %d\n", *port);
            break;

        case '?':
            break;

        }
    }
    debug(LINE);
}

void handler_client(int socket) {
    char input[BUFFER_SIZE];
    do {
        fgets(input, BUFFER_SIZE, stdin);
        fflush(stdin);
        send(socket , input , strlen(input)+1, 0 );
        int p;
        do {
            char buffer[BUFFER_SIZE];
            p = read(socket,buffer,BUFFER_SIZE);
            if (p > 0) {
                printf("%s\n", buffer);
                break;
            }
        } while (p >=0);

    } while (input[0] != 's');
}

int main(int argc, char** argv) {
    char server_ip[IPv4_SIZE];
    int server_port;
    int client_socket;
    struct sockaddr_in server_address;

    debug("Starting the client...\n");

    //Parsing the args
    parse_args(argc, argv, server_ip, &server_port);

    //Creating the socket
    check(client_socket = socket(AF_INET, SOCK_STREAM, 0), "socket", TRUE);

    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(server_port);

    check(connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)), "connect", TRUE);
    debug("Connected with the server.\n");
    handler_client(client_socket);
    debug("Finishing the connection with the server.\n")
    close(client_socket);
}