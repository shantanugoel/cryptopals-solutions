/* Assumes input buffer has appropriate buffer allocated to accommodate padding */
int pad_pkcs(char * buffer, unsigned int buffer_len, unsigned int input_len,
             unsigned int pkcs_num, unsigned int block_size)
{
  unsigned int pad_len = 0;
  if((pkcs_num == 5) && (block_size > 8))
  {
    return -1;
  }
  pad_len = block_size - (input_len % block_size);
  if(buffer_len < (input_len + pad_len))
  {
    return -1;
  }
  for(unsigned int i = 0; i < pad_len; ++i)
  {
    buffer[input_len + i] = pad_len;
  }
  return 0;
}
