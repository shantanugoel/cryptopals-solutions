/* Assumes input buffer has appropriate buffer allocated to accommodate padding */
int pad_pkcs(char * buffer, unsigned int buffer_len, unsigned int input_len,
             unsigned int pkcs_num, unsigned int block_size);

