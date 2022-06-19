#include <stdio.h>
#include <stdlib.h>

void DieWithError(const char *errorMessage) {
  perror(errorMessage);
  exit(EXIT_FAILURE);
}
