#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_SIZE_ASSUMED 512

unsigned int find_repetition_score(char *line, unsigned int size)
{
  unsigned int rep_score = 0;
  /* Operate on blocks of 16 bytes or 32 nibbles as input is hex format */
  for(unsigned int i = 0; i < size; i += 32)
  {
    for(unsigned int j = i + 32; j < (size - 32); j += 32)
    {
      if(strncmp(line + i, line + j, 32) == 0)
      {
        rep_score++;
      }
    }
  }
  return rep_score;
}

int main()
{
  char line[MAX_LINE_SIZE_ASSUMED];
  char possible_line[MAX_LINE_SIZE_ASSUMED];
  unsigned int max_repetition_score = 0;
  FILE * file = fopen("8.txt", "r");

  /*
    Logic would be to read each line and detect if there are any 16 byte blocks repeating in the line.
    Since ECB produces same 16 byte output for same 16 byte input, a repeating pattern in plaintext would
    lead to repeating pattern in ciphertext and would point us towards the possibility of given line being
    encrypted by ECB.
   */

  while(fgets(line, sizeof(line), file))
  {
    unsigned int line_size = strlen(line);
    unsigned int current_repetition_score = find_repetition_score(line, line_size);

    if(current_repetition_score > max_repetition_score)
    {
      strcpy(possible_line, line);
      max_repetition_score = current_repetition_score;
    }
  }
  if(max_repetition_score > 0)
  {
    printf("%s", possible_line);
  }
  return 0;
}
