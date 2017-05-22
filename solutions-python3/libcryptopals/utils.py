#!/usr/bin/env python3

from base64 import b64encode

def hex_to_base64(hex_str):
  return str(object=b64encode(bytes.fromhex(hex_str)), encoding='utf-8')


def fixed_xor(first_buffer, second_buffer):
  if(len(first_buffer) != len(second_buffer)):
    raise ValueError('Both buffers should be of same size')

  output = b''

  for x, y in zip(first_buffer, second_buffer):
    output += bytes([x ^ y])

  return output
