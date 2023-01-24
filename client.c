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
#include "parson.h"

#define BIG_STRING 1000
#define LITTLE_STRING 10

void fatal(char * err_message){
    perror(err_message);
    exit(0);
}

//definitely not stolen
char *strremove(char *str, const char *sub) {
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}

int main() {

     char *message;
     char *response;
     int sockfd;

//34.118.48.238

     char main_server[] = "34.241.4.235";

     char *comand = (char*)calloc(LITTLE_STRING, sizeof(char) );
     if(comand == NULL){
          fatal("{ error: Calloc failed to alloc comand }");
     }

     char **json_buffer=(char**)calloc(LITTLE_STRING, sizeof(char*) );
     if(json_buffer == NULL){
          fatal("{ error: Calloc failed to alloc bufer_register }");
     }

     char *username =(char*)calloc(LITTLE_STRING, sizeof(char) );
     if(username == NULL){
          fatal("{ error: Calloc failed to alloc username }");
     }    
     char *password = (char*)calloc(LITTLE_STRING, sizeof(char) );
     if(password == NULL){
          fatal("{ error: Calloc failed to alloc password }");
     }

     char *cookie_aux = (char*)calloc(BIG_STRING, sizeof(char) );
     if(cookie_aux == NULL){
          fatal("{ error: Calloc failed to alloc cookie_aux }");
     }
     char *cookie = (char*)calloc(BIG_STRING, sizeof(char) );
     if(cookie_aux == NULL){
          fatal("{ error: Calloc failed to alloc cookie }");
     }

     char *token_aux = (char*)calloc(BIG_STRING, sizeof(char) );
     if(token_aux == NULL){
          fatal("{ error: Calloc failed to alloc token_aux }");
     }
     char *token = (char*)calloc(BIG_STRING, sizeof(char) );
     if(token == NULL){
          fatal("{ error: Calloc failed to alloc token }");
     }
     char *TWJ = (char*)calloc(BIG_STRING, sizeof(char) );
     if(TWJ == NULL){
          fatal("{ error: Calloc failed to alloc TWJ }");
     }

     char *id = (char*)calloc(LITTLE_STRING, sizeof(char) );
     if(id == NULL)
     {
          fatal("{ error: Calloc failed to alloc id }");
     }
     char *URL = (char*)calloc(BIG_STRING, sizeof(char) );
     if(URL == NULL)
     {
          fatal("{ error: Calloc failed to alloc URL }");
     }

     char *str_buffer = (char*)calloc(BIG_STRING, sizeof(char) );
     if(str_buffer == NULL)
     {
          fatal("{ error: Calloc failed to alloc str_buffer }");
     }


     
     

     


    while (1){

          scanf("%s", comand);
          if (strcmp(comand, "register") == 0){

               printf("username=");
               scanf("%s", username);
               printf("password=");
               scanf("%s", password);
               JSON_Value *root_value = json_value_init_object();
               JSON_Object *root_object = json_value_get_object(root_value);
               json_object_set_string(root_object, "username", username);
               json_object_set_string(root_object, "password", password);
               
               
              json_buffer[0] = json_serialize_to_string_pretty(root_value);

               sockfd = open_connection (main_server, 8080, AF_INET, SOCK_STREAM, 0);
               message = compute_post_request(main_server, "/api/v1/tema/auth/register", 
                                             "application/json",json_buffer, 1, NULL, 0, NULL);
               send_to_server(sockfd, message);
               response = receive_from_server(sockfd);
               if(strstr(response,"{\"error") != NULL){
                    printf("%s\n", (strstr( response,"{\"error") ) );
                    continue;
               } else {
                    printf("{ Register succesfully }\n");
               }

               json_free_serialized_string(username);
               json_free_serialized_string(password);
               close(sockfd);
          }
          else if (strcmp(comand, "login") == 0){

              

               printf("username=");
               scanf("%s", username);
               printf("password=");
               scanf("%s", password);
               JSON_Value *root_value = json_value_init_object();
               JSON_Object *root_object = json_value_get_object(root_value);
               json_object_set_string(root_object, "username", username);
               json_object_set_string(root_object, "password", password);
               
            
               json_buffer[0] = json_serialize_to_string_pretty(root_value);

               sockfd = open_connection (main_server, 8080, AF_INET, SOCK_STREAM, 0);
               message = compute_post_request(main_server, "/api/v1/tema/auth/login", 
                                             "application/json", json_buffer, 1, NULL, 0, NULL);
               send_to_server(sockfd, message);
               response = receive_from_server(sockfd);

               if(strstr(response,"{\"error") != NULL){
                    printf("%s\n", (strstr( response,"{\"error") ) );
                    continue;
               } else {
                    printf("{ Login succesfully } \n");
               }
               str_buffer = strstr(response, "Set-Cookie:");
               cookie_aux = strtok(str_buffer, "\r\n");
               
           
               cookie = strremove(cookie_aux, "Set-Cookie: ");

               
               json_free_serialized_string(username);
               json_free_serialized_string(password);
               


               close(sockfd);
          }
          else if (strcmp(comand, "enter_library") == 0){

               sockfd = open_connection(main_server, 8080, AF_INET, SOCK_STREAM, 0);
               message = compute_get_request(main_server, "/api/v1/tema/library/access", NULL, &cookie, 1, NULL);
               send_to_server(sockfd, message);

               response = receive_from_server(sockfd);
               str_buffer = strstr(response, "{\"token\":\"");
               token_aux = strtok(str_buffer, "\r\n");
               token = strremove(token_aux, "{\"token\":\"");
               token = strremove(token, "\"}");
               strcpy(TWJ,"Authorization: Bearer ");
               strcat(TWJ, token);
               if(strstr(response,"{\"error") != NULL){
                    printf("%s\n", (strstr( response,"{\"error") ) );
                    continue;
               } else {
                    printf("{ Library acces granted }\n");
               }

               

               close(sockfd);
          }
          else if (strcmp(comand, "get_books") == 0){      

               sockfd = open_connection(main_server, 8080, AF_INET, SOCK_STREAM, 0);
               message = compute_get_request(main_server, "/api/v1/tema/library/books", "application/json", NULL, 0, TWJ);

           
               send_to_server(sockfd, message);

               response = receive_from_server(sockfd);
               if(strstr(response,"{\"error") != NULL){
                    printf("%s\n", (strstr( response,"{\"error") ) );
                    continue;
               } else {
                    printf("%s\n", (strstr( response, "[") ) );
               }
               close(sockfd);               


          }

          else if (strcmp(comand, "get_book") == 0){


               printf("id=");
               scanf("%s", id);
               sockfd = open_connection(main_server, 8080, AF_INET, SOCK_STREAM, 0);
               strcpy(URL, "/api/v1/tema/library/books/");
               strcat(URL,id);

               message = compute_get_request(main_server, URL, "application/json", NULL, 0, TWJ);
               send_to_server(sockfd, message);
               response = receive_from_server(sockfd);
               if(strstr(response,"{\"error") != NULL){
                    printf("%s\n", (strstr( response,"{\"error") ) );
                    continue;
               } else {
                    printf("%s\n", (strstr( response, "[") ) );
               }  
               close(sockfd);         
          }
          else if (strcmp(comand, "add_book") == 0){

               char *title = (char*)calloc(LITTLE_STRING, sizeof(char) );
               if(title == NULL){
                    fatal("{ error: Calloc failed to alloc title }");
               }   
               char *author = (char*)calloc(LITTLE_STRING, sizeof(char) );
               if(author == NULL){
                    fatal("{ error: Calloc failed to alloc author }");
               }
               char *genre = (char*)calloc(LITTLE_STRING, sizeof(char) );
               if(genre == NULL){
                    fatal("{ error: Calloc failed to alloc genre }");
               }
               int page_count;
               char *publisher = (char*)calloc(LITTLE_STRING, sizeof(char) );
               if(publisher == NULL){
                    fatal("{ error: Calloc failed to alloc publisher }");
               }
               char *charValue = (char*)calloc(LITTLE_STRING, sizeof(char) );
               if(charValue == NULL){
                    fatal("{ error: Calloc failed to alloc charValue }");
               }
               printf("title=");
               scanf(" %[^\t\n]s",title);
               printf("author=");
               scanf(" %[^\t\n]s", author);
               printf("genre=");
               scanf(" %[^\t\n]s", genre);
               printf("page_count=");
               scanf("%d", &page_count);
               sprintf(charValue, "%d", page_count);
               printf("publisher=");
               scanf(" %[^\t\n]s", publisher);
               JSON_Value *root_value = json_value_init_object();
               JSON_Object *root_object = json_value_get_object(root_value);
               json_object_set_string(root_object, "title", title);
               json_object_set_string(root_object, "author", author);
               json_object_set_string(root_object, "genre", genre);
               json_object_set_string(root_object, "page_count", charValue);
               json_object_set_string(root_object, "publisher", publisher);
               
               json_buffer[0] = json_serialize_to_string_pretty(root_value);

               sockfd = open_connection (main_server, 8080, AF_INET, SOCK_STREAM, 0);
               message = compute_post_request(main_server, "/api/v1/tema/library/books", 
                                             "application/json", json_buffer, 1, NULL, 0, TWJ);
               send_to_server(sockfd, message);
               response = receive_from_server(sockfd);
               if(strstr(response,"{\"error") != NULL){
                    printf("%s\n", (strstr( response,"{\"error") ) );
                    continue;
               } else {
                    printf("{ Book added succesfully! }\n");
               }

               json_free_serialized_string(title);
               json_free_serialized_string(author);
               json_free_serialized_string(genre);
               json_free_serialized_string(charValue);
               json_free_serialized_string(publisher);
               
               close(sockfd);
               
               
          }


          else if (strcmp(comand, "delete_book") == 0){


               printf("id=");
               scanf("%s", id);
               sockfd = open_connection(main_server, 8080, AF_INET, SOCK_STREAM, 0);
               strcpy(URL, "/api/v1/tema/library/books/");
               strcat(URL,id);
               message = compute_delete_request(main_server, URL, "application/json", NULL, 0, TWJ);
               send_to_server(sockfd, message);

               response = receive_from_server(sockfd);
               if(strstr(response,"{\"error") != NULL){
                    printf("%s\n", (strstr( response,"{\"error") ) );
                    continue;
               } else {
                    printf("{ Book: %s deleted succesfully }\n", id);
               }   
               close(sockfd); 
          }
          else if (strcmp(comand, "logout") == 0){

               sockfd = open_connection(main_server, 8080, AF_INET, SOCK_STREAM, 0);
               message = compute_get_request(main_server, "/api/v1/tema/auth/logout", NULL, &cookie, 1, NULL);
               send_to_server(sockfd, message);
               response = receive_from_server(sockfd);
               if(strstr(response,"{\"error") != NULL){
                    printf("%s\n", (strstr( response,"{\"error") ) );
                    continue;
               } else {
                    printf("{ logout succesfully }\n");
               }
               close(sockfd);
        }
        else if (strcmp(comand, "exit") == 0)
        {
             //here should be a bunch of free
             //but idk how to fix the seq fault
             exit(0);
        }
    
    }
    

    return 0;
}