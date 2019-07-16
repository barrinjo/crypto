#include <stdio.h>
#include <string.h>

void decrypt(char file_name[], int private_key) {
  FILE *ifstream_ptr;
  ifstream_ptr = fopen(file_name, "rb");

  long int file_size;
  fseek(ifstream_ptr, 0L, SEEK_END);
  file_size = ftell(ifstream_ptr);
  rewind(ifstream_ptr);

  unsigned char buffer[file_size];
  fread(buffer, sizeof(buffer), 1, ifstream_ptr);
  fclose(ifstream_ptr);

  for (size_t i = 0; i < file_size; i++) {
    buffer[i] -= private_key;
  }

  FILE *ofstream_ptr;
  ofstream_ptr = fopen(file_name, "wb");
  fwrite(buffer, sizeof(buffer), 1, ofstream_ptr);
  fclose(ofstream_ptr);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("no file name given");
  } else {
    printf("enter key: ");
    int input;
    scanf("%d", &input);
    decrypt(argv[1], input % 30);
  }
  return 0;
}