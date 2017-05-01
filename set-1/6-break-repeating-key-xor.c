#include <stdio.h>

unsigned int count_bits(char num)
{
  unsigned int count = 0;
  for(unsigned int i = 0; (i < sizeof(char) * 8) && (num != 0); ++i)
  {
    if(num & (0x1 << i))
    {
      count++;
    }
  }
  return count;
}

unsigned int get_hamming_distance(char * str1, char * str2)
{
  unsigned int count = 0;
  unsigned char1 = '\0';
  unsigned char2 = '\0';
  while(*str1 || *str2)
  {
    if(*str1)
    {
      char1 = *str1;
      str1++;
    }
    else
    {
      char1 = '\0';
    }
    if(*str2)
    {
      char2 = *str2;
      str2++;
    }
    else
    {
      char2 = '\0';
    }
    count += count_bits(char1 ^ char2);
  }
  return count;
}

int main()
{
  printf("%u\n", get_hamming_distance("this is a test", "wokka wokka!!!"));
}
