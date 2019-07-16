#include <stdio.h>

int main() {
  // unsigned char buffer[20];
  FILE *stream_ptr;
  stream_ptr = fopen("megaman.png", "rb");

  long int file_size;
  fseek(stream_ptr, 0L, SEEK_END);
  file_size = ftell(stream_ptr);
  rewind(stream_ptr);

  unsigned char buffer[file_size];

  fread(buffer, sizeof(buffer), 1, stream_ptr);

  for (size_t i = 0; i < file_size; i++) {
    printf("%u ", buffer[i]);
  }

  return 0;
}
