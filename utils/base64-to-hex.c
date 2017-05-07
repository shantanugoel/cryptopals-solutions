#include <stdio.h>
#include <string.h>
#include "utils.h"

#define OUTPUT_BUFFER_LENGTH 1000

char output_buffer[OUTPUT_BUFFER_LENGTH] = {0};

int main(int argc, char *argv[])
{
  int result = 0;
  if(argc == 2)
  {
    result = base64_to_hex(argv[1], output_buffer, strlen(argv[1]), OUTPUT_BUFFER_LENGTH);
    if(result >= 0)
    {
      printf("%s", output_buffer);
    }
  }
  return result;
}
