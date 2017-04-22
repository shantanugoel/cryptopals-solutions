#include <stdio.h>
#include <string.h>

char input1[] = "1c0111001f010100061a024b53535009181c";
char input2[] = "686974207468652062756c6c277320657965";
char output[38];
char lookup[17] = "0123456789abcdef";


unsigned int hex2dec(char nibble)
{
  unsigned int val = 0;
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

int main()
{
  unsigned int input_length = strlen(input1);
  unsigned int num1 = 0, num2 = 0, op_num = 0;;
  for(unsigned int i = 0; i < input_length; ++i)
  {
    num1 = hex2dec(input1[i]);
    num2 = hex2dec(input2[i]);
    op_num = num1 ^ num2;
    output[i] = lookup[op_num];
  }
  printf("Input1: %s\nInput2: %s\nOutput: %s", input1, input2, output);
  return 0;
}
