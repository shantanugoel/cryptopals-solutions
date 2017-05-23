#!/usr/bin/env python3

import binascii
from libcryptopals.utils import repeating_key_xor

input = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal"
key = 'ICE'
expected_output = b"0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f"

output = binascii.hexlify(repeating_key_xor(bytes(input, encoding='utf-8'), bytes(key, encoding='utf-8')))
print(output)

if output == expected_output:
  print("Success!")
