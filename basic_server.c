#include "pipe_networking.h"
#include <string.h>

void to_upper(char * s) {

  int i=0;
  while (i<strlen(s))
    s[i++]-=32;

}

int main() {

  int to_client;
  int from_client;


  from_client = server_handshake( &to_client );

  while (1) {

    char s[256];
    read(from_client,s,256);
    printf("Modifying string\n");
    to_upper(s);
    write(to_client,s,256);



  }

}
