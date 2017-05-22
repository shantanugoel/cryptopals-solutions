#!/usr/bin/env python3

from base64 import b64encode

def hex_to_base64(hex_str):
  return str(object=b64encode(bytes.fromhex(hex_str)), encoding='utf-8')
