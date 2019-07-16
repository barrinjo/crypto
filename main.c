#include <stdio.h>

int main() {
  unsigned char buffer[20];
  FILE *stream_ptr;

  stream_ptr = fopen("file", "rb");
  fread(buffer, sizeof(buffer), 1, stream_ptr);

  for (size_t i = 0; i < 20; i++) {
    printf("%u ", buffer[i]);
  }

  return 0;
}
