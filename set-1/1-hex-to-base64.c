#include <stdio.h>
#include <string.h>

char input[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
char output[200];
char base64_lookup_table[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


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
  unsigned int input_length = strlen(input);
  unsigned int leftover_bits = 4;
  unsigned int bits_needed = 6;
  unsigned int num = 0;
  /* Iterate over complete input string */
  for(unsigned int i = 0, j = 0; i < input_length; ++i)
  {
    /* Parse the character freshly pulled from input string */
    do
    {
      /*
       We follow a sliding window kind of design.
       Create a 6 bit base64 number window and keep filling it by pulling numbers off
       the input string. If the window is not filled by a number, pull the next number.
       As soon as the window is filled, convert and push to output. Save the number of bits
       which couldn't be used in this window and process those again towards the next window
       without pulling the next number.
       */
      int shift_amount = bits_needed - leftover_bits;
      unsigned int input_val = 0;
      if(shift_amount > 0)
      {
        input_val = hex2dec(input[i]) << (shift_amount);
        bits_needed -= leftover_bits;
        leftover_bits = 0;
      }
      else
      {
        input_val = hex2dec(input[i]) >> (-1 * shift_amount);
        leftover_bits -= bits_needed;
        bits_needed = 0;
      }
      num = (num | input_val) & 0x3F;
      if(bits_needed == 0)
      {
        output[j] = base64_lookup_table[num];
        ++j;
        num = 0;
        bits_needed = 6;
      }
    } while(leftover_bits);
    leftover_bits = 4;
  }
  printf("Input: %s\nOutput: %s", input, output);
  return 0;
}
