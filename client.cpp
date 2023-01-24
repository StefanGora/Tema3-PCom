#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

using namespace std;

int main() {

    char *message;
    char *response;
    int sockfd;

    char main_server[] = "34.118.48.238";

    sockfd = open_connection (main_server, 8080, AF_INET, SOCK_STREAM, 0);
    message = compute_get_request(main_server, "/api/v1/tema/library/access", NULL, NULL, 0);
    send_to_server(sockfd, message);

    response = receive_from_server(sockfd);

    
    char *comand = (char*)malloc(sizeof(char*)*10);
    

    /*while (1)
    {
        
        scanf("%s", comand);
        if (strcmp(comand, "register") == 0){
            cout << "Undifiend yet";
        }
        else if (strcmp(comand, "login") == 0){
             cout << "Undifiend yet";
        }
        else if (strcmp(comand, "enter_library") == 0)
        {
             cout << "Undifiend yet";
        }
        else if (strcmp(comand, "get_books") == 0)
        {
             cout << "Undifiend yet";
        }
        else if (strcmp(comand, "delete_books") == 0)
        {
             cout << "Undifiend yet";
        }
        else if (strcmp(comand, "logout") == 0)
        {
             cout << "Undifiend yet";
        }
        else if (strcmp(comand, "exit") == 0)
        {
             exit(0);
        }
        
        
        
    }*/
    

    return 0;
}