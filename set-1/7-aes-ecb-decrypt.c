#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>
#include "../utils/utils.h"

unsigned int get_file_size(FILE * file)
{
  unsigned int size = 0;
  fseek(file, 0L, SEEK_END);
  size = ftell(file);
  rewind(file);
  return size;
}

int decrypt(unsigned char *ciphertext, unsigned int ciphertext_len, unsigned char *key, unsigned char *plaintext)
{
  AES_KEY enc_key;
  AES_set_decrypt_key(key, 128, &enc_key);
  for(unsigned int i = 0; i < ciphertext_len; i += 16)
  {
    AES_ecb_encrypt(ciphertext + i, plaintext + i, &enc_key, AES_DECRYPT);
  }
  return 0;
}

int main()
{
  unsigned char * input_b64 = NULL, * input_hex = NULL, * input_str = NULL, *output_str = NULL;
  unsigned int hex_len = 0;
  unsigned int file_size = 0;
  unsigned char *key = "YELLOW SUBMARINE";
  FILE* file = fopen("7.txt", "r");
  file_size = get_file_size(file);
  /* Hex is 4 bits and base64 is 6 bits. So 1.5 times the base64'ed data should be good enough
     to hold the corresponding hex data. A little bit generally but would be taken care by the fact
     that input also has newlines which will not be there in hex */
  input_b64 = malloc(sizeof(char) * file_size + 1);
  input_hex = malloc(sizeof(char) * file_size * 1.5);
  input_str = malloc(sizeof(char) * (file_size * 1.5));
  output_str = malloc(sizeof(char) * (file_size * 1.5) / 2 + 1);

  fread(input_b64, file_size, 1, file);

  hex_len = base64_to_hex(input_b64, input_hex, file_size + 1, file_size * 1.5);

  hex_to_str(input_hex, input_str, hex_len, hex_len / 2);

  decrypt(input_str, hex_len / 2, key, output_str);
  output_str[hex_len / 2 ] = '\0';
  printf("%s", output_str);
  free(input_b64);
  free(input_hex);
  free(input_str);
  free(output_str);
}
