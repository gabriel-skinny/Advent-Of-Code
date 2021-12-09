#include <stdio.h>
#include "syscall.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZEBUFFER 100000

int formatBuffer(char *, char**);
int countMessurmentIncrements(char **, int);

int main(int argc, char *argv[]) {
  char *buffer = malloc(sizeof(char) * SIZEBUFFER);
  char *formatedArr[SIZEBUFFER];
  int fd, counter, stringsRead;

  if (argc < 2) {
    printf("Minimal arguments is 1");
    return -1;
  }

  fd = open(argv[1], O_RDONLY);
  read(fd, buffer, SIZEBUFFER);

  stringsRead = formatBuffer(buffer, formatedArr);
  counter = countMessurmentIncrements(formatedArr, stringsRead);

  printf("\nCounter: %d\n\n", counter);

}

#define READARRMAX 200

int formatBuffer(char *buffer, char **formatedBuffer) {
  char readBuff[READARRMAX];
  int c, numberstringCopied;

  numberstringCopied = c = 0;

  while(*buffer) {
    readBuff[c++] = *buffer;

    if (*buffer++ == '\n') {
      readBuff[c] = '\0';
      *formatedBuffer = malloc (sizeof(char) * READARRMAX);
      strcpy(*formatedBuffer++, readBuff);
      c = 0;
      numberstringCopied++;
    }
  }

  return numberstringCopied;
}

int countMessurmentIncrements(char **buffer, int limit) {
  int counter;

  for (counter = 0; limit - 1 > 0; *buffer++, limit--) {

    if (atoi(*buffer) < atoi(*(buffer + 1))){
      counter++;
    }
  }

  return counter;
}