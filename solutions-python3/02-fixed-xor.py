#!/usr/bin/env python3

from libcryptopals.utils import fixed_xor
from binascii import b2a_hex

h1 = '1c0111001f010100061a024b53535009181c'
h2 = '686974207468652062756c6c277320657965'

expected_output = '746865206b696420646f6e277420706c6179'

output = str(
  object=b2a_hex(
    (
      fixed_xor(
      bytes.fromhex(h1),
      bytes.fromhex(h2))
    )
  ),
  encoding='utf-8'
)

print(output)

if output == expected_output:
  print('Success!')
