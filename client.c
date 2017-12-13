#include "pipe_networking.h"
#include <string.h>

int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  while (1) {

    char s[256];
    printf("Input a string (all letters, all lowercase): ");
    fgets(s,256,stdin);
    s[strlen(s)-1]=0;
    //printf("input read in to s: [%s]\n",s);
    write(to_server,s,256);
    //printf("wrote text\n");
    read(from_server,s,256);
    printf("Received modified string: [%s]\n",s);


  }
}
