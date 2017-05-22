#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/utils.h"

#define MIN_KEY_SIZE 2
#define MAX_KEY_SIZE 40
#define NUM_KEYS_TO_TRY 4

#define KEYSPACE_BEGIN 32
#define KEYSPACE_END   127


unsigned int get_file_size(FILE * file)
{
  unsigned int size = 0;
  fseek(file, 0L, SEEK_END);
  size = ftell(file);
  rewind(file);
  return size;
}

char get_single_char_key_transposed(
  char *input, unsigned input_length, unsigned int keysize,
  unsigned int offset, char * key)
{
  unsigned int current_score = 0, max_score = 0;
  int current_max_score_key = -1;
  for(unsigned int i = KEYSPACE_BEGIN; i <= KEYSPACE_END; ++i)
  {
    char num = 0;
    current_score = 0;
    for(unsigned int j = 0; j < input_length / keysize; j ++)
    {
      num = input[j * keysize + offset] ^ i;
      current_score += get_char_frequency_score(num);
    }
    if(current_score > max_score)
    {
      max_score = current_score;
      current_max_score_key = i;
    }
  }
  *key = current_max_score_key;
  return max_score;
}

void generate_probable_key_size_sorted_list(char * input, unsigned int keysize_list[])
{
  double keysize_list_avg_distance[MAX_KEY_SIZE - MIN_KEY_SIZE] = {INT_MAX};
  for(unsigned int keysize = MIN_KEY_SIZE; keysize <= MAX_KEY_SIZE; ++keysize)
  {
    keysize_list_avg_distance[keysize - MIN_KEY_SIZE] = (
      (get_hamming_distance(&input[0], &input[keysize], keysize) / (double) keysize) +
      (get_hamming_distance(&input[keysize], &input[2 * keysize], keysize) / (double) keysize) +
      (get_hamming_distance(&input[3 * keysize], &input[4 * keysize], keysize) / (double) keysize) +
      (get_hamming_distance(&input[5 * keysize], &input[6 * keysize], keysize) / (double) keysize)
      ) / 4;
  }
  for(unsigned int i = 0; i < MAX_KEY_SIZE - MIN_KEY_SIZE; ++i)
  {
    keysize_list[i] = MIN_KEY_SIZE + i;
  }
  for(unsigned int i = 0; i < MAX_KEY_SIZE - MIN_KEY_SIZE; ++i)
  {
    for(unsigned int j = i + 1; j < MAX_KEY_SIZE - MIN_KEY_SIZE; ++j)
    {
      if(keysize_list_avg_distance[i] > keysize_list_avg_distance[j])
      {
        double temp = keysize_list_avg_distance[i];
        unsigned int temp_key = keysize_list[i];
        keysize_list_avg_distance[i] = keysize_list_avg_distance[j];
        keysize_list_avg_distance[j] = temp;
        keysize_list[i] = keysize_list[j];
        keysize_list[j] = temp_key;
      }
    }
  }
}

int main()
{
  char * input_b64 = NULL, * input_hex = NULL, * input_str = NULL;
  unsigned int keysize_list[MAX_KEY_SIZE - MIN_KEY_SIZE] = {0};
  char keylist[NUM_KEYS_TO_TRY][MAX_KEY_SIZE];
  unsigned int keylist_score[NUM_KEYS_TO_TRY] = {0};
  unsigned int best_key_pos = 0;
  unsigned int best_key_score = 0;
  unsigned int file_size = 0;
  FILE* file = fopen("6.txt", "r");
  file_size = get_file_size(file);
  /* Hex is 4 bits and base64 is 6 bits. So 1.5 times the base64'ed data should be good enough
     to hold the corresponding hex data. A little bit generally but would be taken care by the fact
     that input also has newlines which will not be there in hex */
  input_b64 = malloc(sizeof(char) * file_size + 1);
  input_hex = malloc(sizeof(char) * file_size * 1.5);
  input_str = malloc(sizeof(char) * (file_size * 1.5) / 2 + 1);

  fread(input_b64, file_size, 1, file);

  base64_to_hex(input_b64, input_hex, file_size + 1, file_size * 1.5);

  hex_to_str(input_hex, input_str, file_size * 1.5, (file_size * 1.5) / 2 + 1);

  generate_probable_key_size_sorted_list(input_str, keysize_list);

  for(unsigned int i = 0; i < NUM_KEYS_TO_TRY; ++i)
  {
    for(unsigned int j = 0; j < keysize_list[i]; ++j)
    {
      keylist_score[i] += get_single_char_key_transposed(
        input_str, (file_size * 1.5) /2 + 1, keysize_list[i], j, &keylist[i][j]);
    }
    keylist[i][keysize_list[i]] = '\0';
  }
  for(unsigned int i = 0; i < NUM_KEYS_TO_TRY; ++i)
  {
    if(keylist_score[i] > best_key_score)
    {
      best_key_score = keylist_score[i];
      best_key_pos = i;
    }
  }
  printf("%s", keylist[best_key_pos]);
}
