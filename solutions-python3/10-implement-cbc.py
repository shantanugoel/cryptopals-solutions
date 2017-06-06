#!/usr/bin/env python3

from libcryptopals.aes import AES_DECRYPT, aes_cbc_decrypt
import base64, binascii

input = base64.b64decode(open('10.txt').read())
key = b'YELLOW SUBMARINE'
iv = bytes('\x00' * len(key), encoding='utf-8')

print(aes_cbc_decrypt(input, key, iv).decode())
