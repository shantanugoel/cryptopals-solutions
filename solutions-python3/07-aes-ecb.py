#!/usr/bin/env python3

from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
import base64, binascii

input = base64.b64decode(open('7.txt').read())

key = b'YELLOW SUBMARINE'

cipher = Cipher(algorithms.AES(key), modes.ECB(), backend=default_backend())

decryptor = cipher.decryptor()
print(decryptor.update(input) + decryptor.finalize())
