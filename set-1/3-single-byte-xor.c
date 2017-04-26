#include <stdio.h>
#include <string.h>

char input[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
char keyspace[] = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
/* Scoring space is found from wikipedia and organized in order of most frequently occuring chars
   to least and capital letter being given slightly less score than small letters */
char scoring_space[] = " eEtTaAoOiInNsShHrRdDlLcCuUmMwWfFgGyYpPbBvVkKjJxXqQzZ";

char hex2dec(char nibble)
{
  char val = 0;
  switch(nibble)
  {
    case '0':
      val = 0;
      break;

    case '1':
      val = 1;
      break;

    case '2':
      val = 2;
      break;

    case '3':
      val = 3;
      break;

    case '4':
      val = 4;
      break;

    case '5':
      val = 5;
      break;

    case '6':
      val = 6;
      break;

    case '7':
      val = 7;
      break;

    case '8':
      val = 8;
      break;

    case '9':
      val = 9;
      break;

    case 'a':
    case 'A':
      val = 10;
        break;

    case 'b':
    case 'B':
      val = 11;
      break;

    case 'c':
    case 'C':
      val = 12;
      break;

    case 'd':
    case 'D':
      val = 13;
      break;

    case 'e':
    case 'E':
      val = 14;
      break;

    case 'f':
    case 'F':
      val = 15;
      break;
  }
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
  unsigned int input_length = strlen(input);
  unsigned int keyspace_length = strlen(keyspace);
  unsigned int current_score = 0, max_score = 0;
  int current_max_score_key_pos = -1;
  for(unsigned int i = 0; i < keyspace_length; ++i)
  {
    /*
      Each key is of 2 nibbles, so encrypts/XORs two
      chars (2 nibbles) in given hex encoded string
    */
    char num = 0;
    current_score = 0;
    for(unsigned int j = 0; j < input_length; j += 2)
    {
      num = ((hex2dec(input[j]) ^ (keyspace[i] >> 4)) << 4) |
        (hex2dec(input[j + 1]) ^ (keyspace[i] & 0x0F));
      current_score += get_score(num);
    }
    if(current_score > max_score)
    {
      max_score = current_score;
      current_max_score_key_pos = i;
    }
  }
  printf("Input: %s\nKey found: %c\nScore: %u\n", input,
         keyspace[current_max_score_key_pos], max_score);
  printf("Original String: ");
  for(unsigned int i = 0; i < input_length; i+= 2)
  {
    printf("%c", ((hex2dec(input[i]) ^ (keyspace[current_max_score_key_pos] >> 4)) << 4) |
           (hex2dec(input[i + 1]) ^ (keyspace[current_max_score_key_pos] & 0x0F)));
  }
  return 0;
}
