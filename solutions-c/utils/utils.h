unsigned int hex_to_dec(char nibble);


unsigned int base64_to_dec(char input);

unsigned int base64_to_hex(char * input, char * output,
                  unsigned int input_length, unsigned int output_length);


unsigned int count_bits(char num);

unsigned int get_hamming_distance(char * str1, char * str2, unsigned int length);

unsigned int get_char_frequency_score(char num);

void hex_to_str(char * input, char * output, unsigned input_len, unsigned output_len);
