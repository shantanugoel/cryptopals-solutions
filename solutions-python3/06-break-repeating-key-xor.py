#!/usr/bin/env python3

import operator, base64
from libcryptopals.utils import get_hamming_distance, find_key_single_byte_xor

expected_output = 'Terminator X: Bring the noise'

KEYSIZE_MIN = 2
KEYSIZE_MAX = 40

f = open("6.txt")
input = f.read()
buffer = base64.b64decode(input)

edit_distance_per_keysize = {}

for keysize in range(KEYSIZE_MIN, KEYSIZE_MAX + 1):
  distance = get_hamming_distance(buffer[0: keysize], buffer[keysize: 2 * keysize]) / keysize + \
             get_hamming_distance(buffer[1 * keysize: 2 * keysize], buffer[2 * keysize: 3 * keysize]) / keysize + \
             get_hamming_distance(buffer[2 * keysize: 3 * keysize], buffer[3 * keysize: 4 * keysize]) / keysize + \
             get_hamming_distance(buffer[3 * keysize: 4 * keysize], buffer[4 * keysize: 5 * keysize]) / keysize
  edit_distance_per_keysize[keysize] = distance / 4

sorted_keysize_by_distance = sorted(edit_distance_per_keysize.items(), key=operator.itemgetter(1))

# Choose 3 lowest keysizes
possible_keysizes = [sorted_keysize_by_distance[0][0], sorted_keysize_by_distance[1][0], sorted_keysize_by_distance[2][0]]
possible_keys = {}

for keysize in possible_keysizes:
  score = 0
  key = ''
  for i in range(0, keysize):
    temp_key, temp_score = find_key_single_byte_xor(buffer[i::keysize])
    score += temp_score
    key += chr(temp_key)
  possible_keys[key] = score

output = max(possible_keys.items(), key=operator.itemgetter(1))[0]
print(output)

if output == expected_output:
  print('Success!')
