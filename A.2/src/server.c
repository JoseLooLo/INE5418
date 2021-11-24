#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <server.h>
#include <common.h>

void parse_args(int argc, char**argv, int* port) {
    *port = 5050;
    int opt;
    debug(LINE);
    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch (opt)
        {
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

void handler_server(int client_socket) {
    char buffer[BUFFER_SIZE];
    do {
        int a;
        do {
            a = recv(client_socket,buffer,BUFFER_SIZE,0);
            if (a < 0) return;
        } while (a <= 0);
        debug("Received %s", buffer);
        //Let's just tokenize everything and find what kind of operation the client wants
        char tokens_ad [OPERATION_SIZE][BUFFER_SIZE];
        char tokens_sb [OPERATION_SIZE][BUFFER_SIZE];
        char tokens_ml [OPERATION_SIZE][BUFFER_SIZE];
        char tokens_dv [OPERATION_SIZE][BUFFER_SIZE];

        char* token;
        char* rest = buffer;
        //+
        int tokens_count_ad = 0;
        while ((token = strtok_r(rest, "+", &rest)) != NULL) {
            strcpy(tokens_ad[tokens_count_ad++], token);
        }
        //-
        rest = buffer;
        int tokens_count_sb = 0;
        while ((token = strtok_r(rest, "-", &rest)) != NULL) {
            strcpy(tokens_sb[tokens_count_sb++], token);
        }
        //*
        rest = buffer;
        int tokens_count_ml = 0;
        while ((token = strtok_r(rest, "*", &rest)) != NULL) {
            strcpy(tokens_ml[tokens_count_ml++], token);
        }
        // /
        rest = buffer;
        int tokens_count_dv = 0;
        while ((token = strtok_r(rest, "/", &rest)) != NULL) {
            strcpy(tokens_dv[tokens_count_dv++], token);
        }
        char result[BUFFER_SIZE];
        if (tokens_count_ad == 2) {
            int temp = atoi(tokens_ad[0]) + atoi(tokens_ad[1]);
            snprintf(result, BUFFER_SIZE, "%d", temp);
        } else if (tokens_count_sb == 2) {
            int temp = atoi(tokens_sb[0]) - atoi(tokens_sb[1]);
            snprintf(result, BUFFER_SIZE, "%d", temp);
        } else if (tokens_count_ml == 2) {
            int temp = atoi(tokens_ml[0]) * atoi(tokens_ml[1]);
            snprintf(result, BUFFER_SIZE, "%d", temp);
        } else if (tokens_count_dv == 2) {
            int temp = atoi(tokens_dv[0]);
            if (!temp) {
                char temp[] = "Invalid value.";
                strcpy(result, temp);
            } else {
                int temp = atoi(tokens_dv[0]) / atoi(tokens_dv[1]);
                snprintf(result, BUFFER_SIZE, "%d", temp);
            }
        } else if (buffer[0] == 's') {
            char temp[] = "saindo..";
            strcpy(result, temp);
        }
        write(client_socket, result, BUFFER_SIZE);
        debug("Sending %s\n", result);
    } while (buffer[0] != 's');
}

int main(int argc, char** argv) {
    int server_port;
    int server_socket;
    struct sockaddr_in server_address;

    debug("Starting the server...\n");

    //Parsing the args
    parse_args(argc, argv, &server_port);

    //Creating the socket
    check(server_socket = socket(AF_INET, SOCK_STREAM, 0), "socket", TRUE);

    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(server_port);

    check(bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address)), "bind", TRUE);
    check(listen(server_socket, MAX_CLIENTS), "listen", TRUE);

    while(TRUE) {
        int client_socket;
        check(client_socket = accept(server_socket, (struct sockaddr *)NULL, NULL), "accept", TRUE);
        debug("New accepted client.\n")
        handler_server(client_socket);
        debug("Closing the client socket.\n");
        close(client_socket);
    }
}