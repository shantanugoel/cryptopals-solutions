#!/usr/bin/env python3

from libcryptopals.utils import pad_pkcs

input = "YELLOW SUBMARINE"
expected_output = "YELLOW SUBMARINE\x04\x04\x04\x04"
output = pad_pkcs(input, 7, 20)
print(output)
if output == expected_output:
  print('Success!')
