#include <stdio.h>
#include "utils.h"

char hex_lookup[] = "0123456789abcdef";

unsigned int hex_to_dec(char nibble)
{
  char val = 0;
  if(nibble > 'a') { val = nibble - 'a' + 10; }
  else if(nibble > 'A') { val = nibble - 'A' + 10; }
  else { val = nibble - '0'; }
  return val;
}

unsigned int base64_to_dec(char input)
{
  int val = 0;
  val = input - '/';
  if(input == '=')
  {
    val = 0;
  }
  else if(input == '/')
  {
    val = 63;
  }
  else if(input == '+')
  {
    val = 62;
  }
  else
  {
    val = input - 'a';
    if(val >= 0 )
    {
      val = val + 26;
    }
    else
    {
      val = input - 'A';
      if(val < 0)
      {
        val = input - '0' + 52;
      }
    }
  }
  return (unsigned int) val;
}

unsigned int extract_n_lower_bits(unsigned int num, unsigned int n)
{
  unsigned int shift_amount = 8 * sizeof(unsigned int) - n;
  return ((num << shift_amount) >> shift_amount);
}

unsigned int extract_bit_range(unsigned int num, unsigned begin, unsigned int end)
{
  unsigned int left_shift_amount = 8 * sizeof(unsigned int) - 1 - end;
  unsigned int right_shift_amount = left_shift_amount + begin;
  return ((num << left_shift_amount) >> right_shift_amount);
}

int base64_to_hex(char * input, char * output,
                  unsigned int input_length, unsigned int output_length)
{
  unsigned current_num = 0, leftover_bits = 6, needed_bits = 4, output_val = 0;
  unsigned int i = 0, j = 0;
  int result = 0;
  for(i = 0, j = 0; (i < input_length) && (j < output_length - 1); ++i)
  {
    /* Skip newlines in input stream */
    if(input[i] == '\n')
    {
      continue;
    }
    current_num = base64_to_dec(input[i]);
    leftover_bits = 6;
    do
    {
      unsigned int bit_range_end = leftover_bits - 1;
      unsigned int bit_range_begin = 0;
      unsigned int extracted_bits = 0;
      if(bit_range_end >= needed_bits)
      {
        bit_range_begin = bit_range_end - needed_bits + 1;
      }
      extracted_bits = bit_range_end - bit_range_begin + 1;
      output_val |= (extract_bit_range(current_num, bit_range_begin, bit_range_end) <<
          (needed_bits - extracted_bits));
      leftover_bits -= extracted_bits;
      if(extracted_bits == needed_bits)
      {
        output[j] = hex_lookup[output_val];
        output_val = 0;
        needed_bits = 4;
        ++j;
      }
      else
      {
        needed_bits -= extracted_bits;
      }
    } while(leftover_bits);
  }
  if(i < input_length)
  {
    /* Not able to process complete input due to insufficient output buffer */
    result = -1;
  }
  else
  {
    output[j] = '\0';
  }
  return result;
}

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
