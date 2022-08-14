/* $Id: socket.c 1.1 1995/01/01 07:11:14 cthuang Exp $
 *
 * This module has been modified by Radim Kolar for OS/2 emx
 */

/***********************************************************************
  module:       socket.c
  program:      popclient
  SCCS ID:      @(#)socket.c    1.5  4/1/94
  programmer:   Virginia Tech Computing Center
  compiler:     DEC RISC C compiler (Ultrix 4.1)
  environment:  DEC Ultrix 4.3 
  description:  UNIX sockets code.
 ***********************************************************************/
 
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int get_sockaddr_in(struct sockaddr_in* ad, const char *host, int clientPort)
{
  ad->sin_port = htons(clientPort);
  for(int i = 0;i < 8; ++ i) {
    ad->sin_zero[i]  = 0;
  }
  in_addr_t inaddr = inet_addr(host);
  if (inaddr != INADDR_NONE)
      memcpy(&ad->sin_addr, &inaddr, sizeof(inaddr));
  else
  {
      struct hostent *hp = gethostbyname(host);
      if (hp == NULL)
          return -1;
      memcpy(&ad->sin_addr, hp->h_addr, hp->h_length);
  }
  ad->sin_family = AF_INET;
  return 0;
}

int Socket(const struct sockaddr_in* const ad) {
    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        return sock;
    if (connect(sock, (struct sockaddr *)ad, sizeof(struct sockaddr_in)) < 0)
        return -1;
    return sock;
}

