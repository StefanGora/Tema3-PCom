#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

char *compute_get_request(char *host, char *url, char *query_params,
                            char **cookies, int cookies_count, char*TWJ)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    char *cookie_buffer = calloc(LINELEN, sizeof(char));

    
    if (query_params != NULL) {
        sprintf(line, "GET %s?%s HTTP/1.1", url, query_params);
    } else {
        sprintf(line, "GET %s HTTP/1.1", url);
    }

    compute_message(message, line);

    
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    
    if (cookies != NULL) {
       strcpy(cookie_buffer, "Cookie: ");

       for(int i = 0; i < cookies_count; i++) {
           strcat(cookie_buffer, cookies[i]);
           if (i < cookies_count - 1)
                strcat(cookie_buffer, "; ");
       }
        compute_message(message, cookie_buffer);
    }
    if (TWJ != NULL){
        compute_message(message, TWJ);
    } 
    
    
    compute_message(message, "");
    return message;
}

char *compute_delete_request(char *host, char *url, char *query_params,
                            char **cookies, int cookies_count, char*TWJ)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    char *cookie_buffer = calloc(LINELEN, sizeof(char));

    
    if (query_params != NULL) {
        sprintf(line, "DELETE %s?%s HTTP/1.1", url, query_params);
    } else {
        sprintf(line, "DELETE %s HTTP/1.1", url);
    }

    compute_message(message, line);

    
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    
    if (cookies != NULL) {
       strcpy(cookie_buffer, "Cookie: ");

       for(int i = 0; i < cookies_count; i++) {
           strcat(cookie_buffer, cookies[i]);
           if (i < cookies_count - 1)
                strcat(cookie_buffer, "; ");
       }
        compute_message(message, cookie_buffer);
    }
    if (TWJ != NULL){
        compute_message(message, TWJ);
    } 
    
    
    compute_message(message, "");
    return message;
}

char *compute_post_request(char *host, char *url, char* content_type, char **body_data,
                            int body_data_fields_count, char **cookies, int cookies_count, char* TWJ)
{
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    char *body_data_buffer = calloc(LINELEN, sizeof(char));
    char *cookie_buffer = calloc(LINELEN, sizeof(char));

    
    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);
    
    
    sprintf(line, "Host: %s", host);
    compute_message(message, line);
    

    sprintf(line, "Content-Type: %s", content_type);
    compute_message(message, line);

    for (int i = 0; i < body_data_fields_count; i++) {        
        if (strlen(body_data_buffer) == 0) {
            strcpy(body_data_buffer, body_data[i]);
        } else {
            strcat(body_data_buffer, "&");
            strcat(body_data_buffer, body_data[i]);
        }
    }

    sprintf(line, "Content-Length: %ld", strlen(body_data_buffer));
    compute_message(message, line);

    
    if (cookies != NULL) {
       strcpy(cookie_buffer, "Cookie: ");

       for(int i = 0; i < cookies_count; i++) {
           strcat(cookie_buffer, cookies[i]);
           if (i < cookies_count - 1)
                strcat(cookie_buffer, "; ");
       }
        compute_message(message, cookie_buffer);
    }

    if (TWJ != NULL){
        compute_message(message, TWJ);
    } 

    
    compute_message(message, "");

    
    memset(line, 0, LINELEN);
    compute_message(message, body_data_buffer);

    free(line);
    return message;
}
