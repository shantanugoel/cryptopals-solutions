#include <stdio.h>
#include <string.h>

#define KEYSPACE_BEGIN 32
#define KEYSPACE_END   127
char input[61];
/* Scoring space is found from wikipedia and organized in order of most frequently occuring chars
   to least and capital letter being given slightly less score than small letters */
char scoring_space[] = " eEtTaAoOiInNsShHrRdDlLcCuUmMwWfFgGyYpPbBvVkKjJxXqQzZ";

char hex2dec(char nibble)
{
  char val = 0;
  if(nibble > 'a') { val = nibble - 'a' + 10; }
  else if(nibble > 'A') { val = nibble - 'A' + 10; }
  else { val = nibble - '0'; }
  return val;
}

unsigned int get_score(char num)
{
  unsigned int result = 0;
  unsigned int scoring_space_len = strlen(scoring_space);
  for(unsigned int i = 0; i < scoring_space_len; ++i)
  {
    if(num == scoring_space[i])
    {
      result = scoring_space_len - i;
      break;
    }
  }
  return result;
}

int main()
{
  unsigned int input_length = sizeof(input);
  unsigned int max_score = 0;
  int max_score_key = -1;
  char max_score_input[61];
  FILE * file = fopen("4.txt", "r");

  while(fgets(input, input_length, file))
  {
    int max_score_key_local = -1;
    unsigned int current_score = 0, max_score_local = 0;
    for(unsigned int i = KEYSPACE_BEGIN; i <= KEYSPACE_END; ++i)
    {
      /*
        Each key is of 2 nibbles, so encrypts/XORs two
        chars (2 nibbles) in given hex encoded string
      */
      char num = 0;
      current_score = 0;
      for(unsigned int j = 0; j < input_length; j += 2)
      {
        num = ((hex2dec(input[j]) ^ (i >> 4)) << 4) |
          (hex2dec(input[j + 1]) ^ (i & 0x0F));
        current_score += get_score(num);
      }
      if(current_score > max_score_local)
      {
        max_score_local = current_score;
        max_score_key_local = i;
      }
    }
    if (max_score_local > max_score)
    {
      max_score = max_score_local;
      max_score_key = max_score_key_local;
      strcpy(max_score_input, input);
    }
  }
  printf("Input: %s\nKey found: %c\nScore: %u\n", max_score_input, max_score_key, max_score);
  printf("Original String: ");
  for(unsigned int i = 0; i < input_length; i+= 2)
  {
    printf("%c", ((hex2dec(max_score_input[i]) ^ (max_score_key >> 4)) << 4) |
           (hex2dec(max_score_input[i + 1]) ^ (max_score_key & 0x0F)));
  }
  return 0;
}
