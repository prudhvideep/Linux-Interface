#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef BUF_LEN
#define BUF_LEN 1000
#endif

int test_main(int argc, char **argv) {
  int input_fd, output_fd;
  int output_options;
  mode_t file_perms;
  ssize_t n_read;

  char buf[BUF_LEN];

  if (argc != 3) {
    fprintf(stderr, "Usage copy src dst");
    return EXIT_FAILURE;
  }

  input_fd = open(argv[1], O_RDONLY);
  if (input_fd < 0) {
    fprintf(stderr, "Error opening input file at %s", argv[1]);
    return EXIT_FAILURE;
  }

  output_options = O_CREAT | O_TRUNC | O_WRONLY;
  file_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

  output_fd = open(argv[2], output_options, file_perms);
  if (output_fd < 0) {
    fprintf(stderr, "Error opening file at %s\n", argv[2]);
    return EXIT_FAILURE;
  }

  while ((n_read = read(input_fd, buf, BUF_LEN)) > 0) {
    if (write(output_fd, buf, n_read) != n_read) {
      fprintf(stderr, "Error wring to the file %s", argv[2]);
      exit(EXIT_FAILURE);
    }
  }

  if (n_read == -1) {
    exit(EXIT_FAILURE);
  }

  if (close(input_fd) == -1) {
    fprintf(stderr, "Error closing the file");
    exit(EXIT_FAILURE);
  }

  if (close(output_fd) == -1) {
    fprintf(stderr, "Error closing the file");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
