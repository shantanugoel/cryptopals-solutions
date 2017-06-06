#!/usr/bin/env python3

from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from libcryptopals.utils import fixed_xor, pad_pkcs, unpad_pkcs

AES_ENCRYPT=0
AES_DECRYPT=1

def aes_ecb(input, key, operation):
  cipher = Cipher(algorithms.AES(key), modes.ECB(), backend=default_backend())
  if operation == AES_ENCRYPT:
    cryptor = cipher.encryptor()
  else:
    cryptor = cipher.decryptor()
  return (cryptor.update(input) + cryptor.finalize())

def aes_cbc_encrypt(input, key, iv):
  block_size = len(key)
  input = pad_pkcs(input, 7, 7)
  input_size = len(input)
  output = b''
  prev_block = iv
  for i in range(0, input_size, block_size):
    temp = input[i: i + block_size]
    output += fixed_xor(prev_block, aes_ecb(temp, key, operation))
    prev_block = temp

  return output

def aes_cbc_decrypt(input, key, iv):
  block_size = len(key)
  input_size = len(input)
  output = b''
  prev_block = iv
  for i in range(0, input_size, block_size):
    temp = input[i: i + block_size]
    output += fixed_xor(prev_block, aes_ecb(temp, key, AES_DECRYPT))
    prev_block = temp

  return unpad_pkcs(output, 7, 7)
