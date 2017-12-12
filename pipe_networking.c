#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  mkfifo(ACK, 0666);
  int up = open(ACK, O_RDONLY , 0666);
  char received[10];
  read(up, received, 8);
  if(!fork()){
    execlp("rm", "rm", ACK, NULL);

  }
  int down = open(received, O_WRONLY, 0666);
  write(down, "confirm", 8);
  read(up, received, 8);
  if(!strcmp(received, "confirm")){
    printf("handshake complete\n");
    *to_client = down;
    return up;
  }
  else{
    return 0;
  }
}
  


/*=========================
  client_handshake
  args: int * to_server

  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int up = open(ACK, O_WRONLY, 0666);  
  mkfifo("bonjour", 0666);
  write(up, "bonjour", 8);
  int down = open("bonjour", O_RDONLY, 0666);
  char received[10];
  read(down, received, 8);
  if(!strcmp(received, "confirm")){
    if(!fork()){
      execlp("rm", "rm", "bonjour", NULL);
    }
    
    write(up, "confirm", 8);
    *to_server = up;
    return down;
  }
  else{
    return 0;
  }
}
