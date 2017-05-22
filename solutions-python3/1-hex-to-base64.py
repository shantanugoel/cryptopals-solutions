#!/usr/bin/env python3

from libcryptopals.utils import hex_to_base64

input = '49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d'

expected_output = 'SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t'

output = hex_to_base64(input)
print(output)
if expected_output == output:
  print("Success!")
