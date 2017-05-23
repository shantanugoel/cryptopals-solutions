#!/usr/bin/env python3

from libcryptopals.utils import english_score, single_byte_xor

expected_output = 'Now that the party is jumping\n'

def get_score_and_key(line):
  max_score = 0
  key = b''
  for k in range(32, 128):
    try:
      score = english_score(str(object=single_byte_xor((line), k), encoding='utf-8'))
      if score > max_score:
        key = k
        max_score = score
    except UnicodeDecodeError:
      pass
  return key, max_score

possible_key = b''
possible_line = ''
max_score = 0
with open('4.txt') as file:
  for line in file:
    line = bytes.fromhex(line.rstrip())
    key, score = get_score_and_key(line)
    if score > max_score:
      possible_line = line
      possible_key = key
      max_score = score

output = str(object=single_byte_xor(possible_line, possible_key), encoding='utf-8')
print(output)
if output == expected_output:
  print('Success!')
