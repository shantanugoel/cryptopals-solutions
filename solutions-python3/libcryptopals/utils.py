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


def repeating_key_xor(buffer, key):
  output = b''
  keylen = len(key)
  i = 0
  for input_byte in buffer:
    #if input_byte == '\n':
      #continue
    output += bytes([input_byte ^ key[i % keylen]])
    i += 1
  return output


def english_score(string):
  score = 0
  scoring_space = " eEtTaAoOiInNsShHrRdDlLcCuUmMwWfFgGyYpPbBvVkKjJxXqQzZ"
  scoring_space_len = len(scoring_space)
  for char in string:
    scoring_space_pos = 0
    for x in scoring_space:
      if x == char:
        score += scoring_space_len - scoring_space_pos
        break
      scoring_space_pos += 1
  return score


def single_byte_xor(buffer, key):
  output = b''
  for input_byte in buffer:
    output += bytes([input_byte ^ key])
  return output
