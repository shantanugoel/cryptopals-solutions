#include <stdio.h>
#include <limits.h>
#include "../utils/utils.h"

#define MIN_KEY_SIZE 2
#define MAX_KEY_SIZE 40

int main()
{
  char string1[MAX_KEY_SIZE + 1] = {0};
  char string2[MAX_KEY_SIZE + 1] = {0};
  double min_distance = INT_MAX;
  unsigned int best_keysize = MIN_KEY_SIZE;
  FILE* file = fopen("6.txt", "r");
  for(unsigned int keysize = 2; keysize <= MAX_KEY_SIZE; ++keysize)
  {
    double distance = 0;
    for(unsigned int i = 0; i < keysize;)
    {
      string1[i] = fgetc(file);
      if(string1[i] != '\n')
      {
        ++i;
      }
    }
    for(unsigned int i = 0; i < keysize;)
    {
      string2[i] = fgetc(file);
      if(string2[i] != '\n')
      {
        ++i;
      }
    }
    string1[keysize] = '\0';
    string2[keysize] = '\0';
    distance = get_hamming_distance(string1, string2) / (double) keysize;
    printf("Keysize:%u Distance: %f\n", keysize, distance);
    if(distance < min_distance)
    {
      min_distance = distance;
      best_keysize = keysize;
    }
  }
  printf("Best guess for keysize: %u\n", best_keysize);
}
