#include <stdio.h>
#include "../utils/padding.h"

int main()
{
  char input[20] = "YELLOW SUBMARINE";
  char expected_output[20] = "YELLOW SUBMARINE\x4\x4\x4\x4";
  int result = 0;
  pad_pkcs(input, 20, 16, 7, 20);
  for(unsigned int i = 0; i < 20; ++i)
  {
    printf("%c", input[i]);
    if(input[i] != expected_output[i])
    {
      result = -1;
      break;
    }
  }
  if(result == 0)
  {
    printf("\nSuccess!\n");
  }
}
