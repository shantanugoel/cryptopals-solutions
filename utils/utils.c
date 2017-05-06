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
  if(val == 0)
  {
    val = 63;
  }
  else
  {
    val = input - '+';
    if(val == 0)
    {
      val = 62;
    }
    else
    {
      val = input - 'a';
      if(val > 0 )
      {
        val = val + 25;
      }
      else
      {
        val = input - 'A';
        if(val < 0)
        {
          val = input - '0';
        }
      }
    }
  }
  return (unsigned int) val;
}

int base64_to_hex(char * input, char * output,
                  unsigned int input_length, unsigned int output_length)
{
  
}
