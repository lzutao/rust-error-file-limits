#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define BUF_SIZE 500

int main(void) {
  for (int i = 0; i < 300; ++i) {
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s, j;
    size_t len;
    ssize_t nread;
    char buf[BUF_SIZE];
    /* Obtain address(es) matching host/port */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;     /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0; /* Any protocol */
    s = getaddrinfo("example.com", "80", &hints, &result);
    if (s != 0) {
      fprintf(stderr, "getaddrinfo: errno: %d, msg: %s\n", s, gai_strerror(s));
      exit(EXIT_FAILURE);
    }
    /* getaddrinfo() returns a list of address structures.
       Try each address until we successfully connect(2).
       If socket(2) (or connect(2)) fails, we (close the socket
       and) try the next address. */
    for (rp = result; rp != NULL; rp = rp->ai_next) {
      sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
      if (sfd == -1)
        continue;
      if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
        break; /* Success */
      close(sfd);
    }

    if (rp == NULL) { /* No address succeeded */
      fprintf(stderr, "Could not connect\n");
      exit(EXIT_FAILURE);
    }

    // don't free, reproduce socket-limits on macOS.
    // freeaddrinfo(result); /* No longer needed */

    /* Send remaining command-line arguments as separate
       datagrams, and read responses from server */
    // {
    //   char const *argv = "wdyt";
    //   len = strlen(argv) + 1;
    //   /* +1 for terminating null byte */
    //   if (len > BUF_SIZE) {
    //     fprintf(stderr, "Ignoring long message in argument %d\n", j);
    //     continue;
    //   }
    //   if (write(sfd, argv, len) != len) {
    //     fprintf(stderr, "partial/failed write\n");
    //     exit(EXIT_FAILURE);
    //   }
    //   nread = read(sfd, buf, BUF_SIZE);
    //   if (nread == -1) {
    //     perror("read");
    //     exit(EXIT_FAILURE);
    //   }
    //   printf("Received %zd bytes: %s\n", nread, buf);
    // }
  }
  exit(EXIT_SUCCESS);
}
