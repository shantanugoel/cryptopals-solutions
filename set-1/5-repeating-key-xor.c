#include <stdio.h>

char input[] = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
char key[] = "ICE";
char lookup[] = "0123456789abcdef";

int main()
{
  for(unsigned int i = 0; i < (sizeof(input) - 1); ++i)
  {
    char num = input[i] ^ key[i % (sizeof(key) - 1)];
    printf("%c%c", lookup[(num >> 4)], lookup[num & 0x0F]);
  }
  return 0;
}
