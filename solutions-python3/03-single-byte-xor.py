#!/usr/bin/env python3

from libcryptopals.utils import english_score, single_byte_xor

input = '1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736'
expected_output = "Cooking MC's like a pound of bacon"

input_bytes = bytes.fromhex(input)
max_score = 0
key = b''
for k in range(32, 128):
  score = english_score(str(object=single_byte_xor(input_bytes, k), encoding='utf-8'))
  if score > max_score:
    key = k
    max_score = score
output = str(object=single_byte_xor(input_bytes, key), encoding='utf-8')
print(output)
if output == expected_output:
  print('Success!')
