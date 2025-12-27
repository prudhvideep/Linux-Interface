#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUF_SIZE 4096

int main(int argc, char **argv) {
  ssize_t n_read;
  if ((argc < 3) || (strcmp(argv[1], "--help") == 0)) {
    fprintf(stderr, "Proper usage tee src_file dst_file");
    exit(EXIT_FAILURE);
  }

  int fd;
  int fd_arr[argc - 1];
  int options = O_CREAT | O_WRONLY | O_TRUNC;
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
  for (int i = 1; i < argc; i++) {
    if ((fd = open(argv[i], options, mode)) < 0) {
      fprintf(stderr, "Error opening the file %s\n", argv[i]);
      exit(EXIT_FAILURE);
    }

    fd_arr[i - 1] = fd;
  }

  char buf[BUF_SIZE];
  while ((n_read = read(0, buf, BUF_SIZE)) > 0) {
    for (int i = 0; i < (argc - 1); i++) {
      if (write(fd_arr[i], buf, n_read) != n_read) {
        fprintf(stderr, "Error opening the file %s\n", argv[i]);
        exit(EXIT_FAILURE);
      }
    }

    if (write(1, buf, n_read) != n_read) {
      fprintf(stderr, "Error writing to stdout\n");
      exit(EXIT_FAILURE);
    }
  }

  for (int i = 0; i < (argc - 1); i++) {
    if (close(fd_arr[i]) < 0) {
      exit(EXIT_FAILURE);
    }
  }

  exit(EXIT_SUCCESS);
}
