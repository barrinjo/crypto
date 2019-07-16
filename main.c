#include <stdio.h>
#include <string.h>
#define PRIVATE_KEY 14;

void encrypt(char file_name[], int private_key) {
  FILE *ifstream_ptr;
  ifstream_ptr = fopen(file_name, "rb");

  long int file_size;
  fseek(ifstream_ptr, 0L, SEEK_END);
  file_size = ftell(ifstream_ptr);
  rewind(ifstream_ptr);

  unsigned char buffer[file_size];

  fread(buffer, sizeof(buffer), 1, ifstream_ptr);

  fclose(ifstream_ptr);

  FILE *ofstream_ptr;
  ofstream_ptr = fopen("output", "wb");
  for (size_t i = 0; i < file_size; i++) {
    // modify each binary value by the private key value to "encrypt file"
    buffer[i] += private_key;
    // printf("%uc ", buffer[i]);
  }
  fwrite(buffer, sizeof(buffer), 1, ofstream_ptr);
}

int create_key() {
  int input;
  printf("enter random number set: ");
  scanf("%d", &input);
  return input % 30;
}

int main(int argc, char *argv[]) {
  if(argc < 2) {
    printf("no file name given.\n");
  } else {

    encrypt(argv[1], create_key());
  }
    

  return 0;
}
