#include <stdio.h>
#include "utils.h"

int main(int argc, char *argv[])
{
  if(argc == 2)
  {
    unsigned int i = 0;
    while(argv[1][i])
    {
      printf("%u", base64_to_dec(argv[1][i]));
      ++i;
    }
  }
  return 0;
}
